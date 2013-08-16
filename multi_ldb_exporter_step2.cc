#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <utility>

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include "leveldb/db.h"
#include "leveldb/write_batch.h"

#include "constants.h"
#include "typedef.h"
#include "comparators.h"
#include "utils.h"

using std::cerr;
using std::cout;
using std::endl;

namespace fs = boost::filesystem;

void load_meta_from_log(MetaMapByIdType& meta_map_by_id,
                        MetaMapByLrgType& meta_map_by_lrange,
                        int& max_ldb_no, std::fstream& log_file) {
  int ldb_no, count;
  std::string lrange, line;

  log_file.seekg(0, std::iostream::beg);
  while (getline(log_file, line)) {
    std::istringstream stream(line);
    stream >> ldb_no;
    if (ldb_no == -1) {
      stream >> ldb_no >> lrange;
      meta_map_by_id.erase(ldb_no);
    } else {
      stream >> lrange >> count;
      meta_map_by_id.insert(MetaMapByIdVtype(ldb_no, std::make_pair(lrange, count)));
      if (ldb_no > max_ldb_no)
        max_ldb_no = ldb_no;
    }
  }
  MetaMapByIdType::iterator map_it = meta_map_by_id.begin();
  while (map_it != meta_map_by_id.end()) {
    meta_map_by_lrange.insert(MetaMapByLrgVtype((map_it->second).first, map_it->first));
    ++map_it;
  }
}

void load_multi_db(DbMapByIdType& db_map_by_id,
                   MetaMapByIdType& meta_map_by_id,
                   const std::string& collectionDir,
                   const leveldb::Options ldb_options) {
  leveldb::Status status;
  MetaMapByIdType::iterator map_it = meta_map_by_id.begin();
  while (map_it != meta_map_by_id.end()) {
    leveldb::DB* db;
    int ldb_no = map_it->first;
    std::string collection_sub_dir_str = collectionDir + "/" + boost::lexical_cast<std::string>(ldb_no);
    status = leveldb::DB::Open(ldb_options, collection_sub_dir_str, &db);
    assert(status.ok());

    db_map_by_id.insert(DbMapByIdVtype(ldb_no, db));
    ++map_it;
  }
}

void update_to_multi_db(DbMapByIdType& db_map_by_id,
                        MetaMapByIdType& meta_map_by_id,
                        int& max_ldb_no,
                        MetaMapByLrgType& meta_map_by_lrange,
                        std::fstream& log_file, std::ifstream& infile,
                        const std::string collectionDir,
                        const leveldb::Options ldb_options) {
  // 准备WriteBatch
  BatchMapByIdType batch_map_by_id;
  DbMapByIdType::iterator map_it1 = db_map_by_id.begin();
  while (map_it1 != db_map_by_id.end()) {
    leveldb::WriteBatch batch;
    batch_map_by_id.insert(BatchMapByIdVtype(map_it1->first, batch));
    ++map_it1;
  }

  // 准备小于所有lrange的WriteBatch和count
  leveldb::WriteBatch over_lrange_batch;
  int over_lrange_count = 0;

  // 更新数据到相应batch
  NumericMapComp numeric_compare;
  MetaMapByIdType old_meta_map_by_id(meta_map_by_id);
  int delimiter_idx;
  std::string line, key, value;
  while (getline(infile, line)) {
    delimiter_idx = line.find('\t');
    key = line.substr(0, delimiter_idx);
    value = line.substr(delimiter_idx + 1);

    int ldb_no = -1;
    MetaMapByLrgType::iterator map_it2 = meta_map_by_lrange.begin();
    while (map_it2 != meta_map_by_lrange.end()) {
      if (numeric_compare(key, map_it2->first)) break;
      ldb_no = map_it2->second;
      ++map_it2;
    }

    if (ldb_no == -1) {
      over_lrange_batch.Put(key, value);
      over_lrange_count++;
    } else {
      batch_map_by_id[ldb_no].Put(key, value);
      meta_map_by_id[ldb_no].second++;
    }
  }

  // 更新batch到leveldb
  leveldb::Status status;
  map_it1 = db_map_by_id.begin();
  while (map_it1 != db_map_by_id.end()) {
    if (meta_map_by_id[map_it1->first].second > old_meta_map_by_id[map_it1->first].second) {
      status = (map_it1->second)->Write(leveldb::WriteOptions(), &batch_map_by_id[map_it1->first]);
      assert(status.ok());
      cout << "update to db: " << map_it1->first << endl;
    }
    ++map_it1;
  }

  // 更新小于所有lrange的数据到新的leveldb中
  if (over_lrange_count > 0) {
    leveldb::DB* db;
    std::string collection_sub_dir_str = collectionDir + "/" + boost::lexical_cast<std::string>(++max_ldb_no);
    status = leveldb::DB::Open(ldb_options, collection_sub_dir_str, &db);
    assert(status.ok());

    status = db->Write(leveldb::WriteOptions(), &over_lrange_batch);
    assert(status.ok());
    cout << "update to over range db: " << max_ldb_no << endl;

    // 更新db_map_by_id
    db_map_by_id.insert(DbMapByIdVtype(max_ldb_no, db));

    // 更新meta_map_by_id和meta_map_by_lrange
    leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
    it->SeekToFirst();
    std::string lrange = it->key().ToString();
    meta_map_by_id.insert(MetaMapByIdVtype(max_ldb_no, std::make_pair(lrange, over_lrange_count)));
    meta_map_by_lrange.insert(MetaMapByLrgVtype(lrange, max_ldb_no));

    // logging
    logging(log_file, meta_map_by_id, max_ldb_no);
  }
}

int main(int argc, char** argv) {
  const std::string collection("global_activity");
  const std::string collectionDir(ldbBaseDir + "/" + collection);

  fs::path collection_path(collectionDir);
  if (!fs::exists(collection_path)) {
    cerr << collectionDir << " doesn't existed" << endl;
    return -1;
  }

  const std::string logStr(collectionDir + "/" + logName);
  std::fstream log_file(logStr.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
  if (!log_file) {
    cerr << "error: unable to open log: "
         << logStr << endl;
    return -1;
  }

  MetaMapByIdType meta_map_by_id;
  MetaMapByLrgType meta_map_by_lrange;
  int max_ldb_no = 0;
  load_meta_from_log(meta_map_by_id, meta_map_by_lrange, max_ldb_no, log_file);

  NumericComparator cmp;
  leveldb::Options options;
  options.comparator = &cmp;
  options.create_if_missing = true;
  DbMapByIdType db_map_by_id;
  load_multi_db(db_map_by_id, meta_map_by_id, collectionDir, options);

  std::string ifile(update_ifile_str);
  std::ifstream infile(ifile.c_str());
  if (!infile) {
    cerr << "error: unable to open file: "
         << ifile << endl;
    return -1;
  }

  update_to_multi_db(db_map_by_id, meta_map_by_id, max_ldb_no, meta_map_by_lrange, log_file, infile, collectionDir, options);

  // 更新后检查各db，并将过大db进行拆分
  std::vector<int> ldb_no_v;
  MetaMapByIdType::iterator map_it = meta_map_by_id.begin();
  while (map_it != meta_map_by_id.end()) {
    int status = divide_to_multi_db(db_map_by_id, map_it->first, max_ldb_no, meta_map_by_id, log_file, collectionDir, options);
    if (status == 0)
      ldb_no_v.push_back(map_it->first);
    ++map_it;
  }
  close_all_mapped_db(db_map_by_id);
  for (int i = 0; i < ldb_no_v.size(); i++)
    destroy_large_db(log_file, meta_map_by_id, ldb_no_v[i], collectionDir);

  infile.close();
  log_file.close();
  cout << "update done! detail: " << logStr << endl;
  return 0;
}
