#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <utility>

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include "leveldb/db.h"
#include "leveldb/write_batch.h"

#include "constants.h"
#include "comparators.h"
#include "utils.h"

using std::cerr;
using std::cout;
using std::endl;

namespace fs = boost::filesystem;

typedef std::map<int, std::pair<std::string, int> > MetaMapByIdType;
typedef MetaMapByIdType::value_type MetaMapByIdVtype;

void write_to_single_db(leveldb::DB*& db, MetaMapByIdType& meta_map_by_id, std::ifstream& infile, int& max_ldb_no) {
  meta_map_by_id.insert(MetaMapByIdVtype(max_ldb_no, std::make_pair("", 0)));

  std::string line, key, value;
  int delimiter_idx;
  leveldb::WriteBatch batch;
  while (getline(infile, line)) {
    delimiter_idx = line.find('\t');
    key = line.substr(0, delimiter_idx);
    value = line.substr(delimiter_idx + 1);
    batch.Put(key, value);
    meta_map_by_id[max_ldb_no].second++;
  }
  leveldb::Status status = db->Write(leveldb::WriteOptions(), &batch);
  assert(status.ok());

  // get the fisrt key
  leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
  it->SeekToFirst();
  meta_map_by_id[max_ldb_no].first = it->key().ToString();
}

void divide_to_multi_db(leveldb::DB*& huge_db, std::string& huge_db_dir_str, MetaMapByIdType& meta_map_by_id, int& max_ldb_no, const std::string& collectionDir, std::fstream& log_file) {
  int new_ldb_no = max_ldb_no;
  NumericComparator cmp;
  leveldb::Options options;
  options.comparator = &cmp;
  options.create_if_missing = true;
  leveldb::Status status;
  leveldb::Iterator* it = huge_db->NewIterator(leveldb::ReadOptions());
  it->SeekToFirst();

  int huge_db_size = meta_map_by_id[max_ldb_no].second;
  if (huge_db_size <= maxDbSize) return;
  while (it->Valid()) {
    std::string colt_sub_dir_str = collectionDir + "/" + boost::lexical_cast<std::string>(++new_ldb_no);
    leveldb::DB* db;
    status = leveldb::DB::Open(options, colt_sub_dir_str, &db);
    assert(status.ok());

    int i = 0;
    leveldb::WriteBatch batch;
    meta_map_by_id.insert(MetaMapByIdVtype(new_ldb_no, std::make_pair(it->key().ToString(), 0)));
    while (i < perDbSize && it->Valid()) {
      batch.Put(it->key(), it->value());
      it->Next();
      i++;
      meta_map_by_id[new_ldb_no].second++;
    }
    status = db->Write(leveldb::WriteOptions(), &batch);
    assert(status.ok());
    delete db;
    cout << "write to sub db: " << colt_sub_dir_str << endl;

    // logging
    logging(log_file, meta_map_by_id, new_ldb_no);
  }

  // destroy huge db
  delete huge_db;
  status = leveldb::DestroyDB(huge_db_dir_str, options);
  cout << "destroy db: " << huge_db_dir_str << endl;
  assert(status.ok());
  logging(log_file, meta_map_by_id, max_ldb_no, "-");
  max_ldb_no = new_ldb_no;
}

bool init_dir(const fs::path& path) {
  bool exists_if = fs::exists(path);

  if (!exists_if) {
    bool create_status = fs::create_directories(path);
    assert(create_status);
    cout << "create dir: " << path.string() << endl;
  }

  return exists_if;
}

int main(int argc, char** argv) {
  const std::string collection("global_activity");
  const std::string collectionDir(ldbBaseDir + "/" + collection);

  fs::path collection_path(collectionDir);
  if (init_dir(collection_path)) {
    cerr << collectionDir << " already existed" << endl;
    return -1;
  }

  const std::string logStr(collectionDir + "/" + logName);
  std::fstream log_file(logStr.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
  if (!log_file) {
    cerr << "error: unable to open log: "
         << logStr << endl;
    return -1;
  } else
    cout << "create log: "
         << logStr << endl;

  int max_ldb_no = 0;
  NumericComparator cmp;
  leveldb::Options options;
  options.comparator = &cmp;
  options.create_if_missing = true;

  leveldb::DB* db;
  std::string collection_sub_dir_str = collectionDir + "/" + boost::lexical_cast<std::string>(++max_ldb_no);
  leveldb::Status status = leveldb::DB::Open(options, collection_sub_dir_str, &db);
  assert(status.ok());

  std::string ifile("data/global_activity.csv");
  std::ifstream infile(ifile.c_str());
  if (!infile) {
    cerr << "error: unable to open file: "
         << ifile << endl;
    return -1;
  }

  MetaMapByIdType meta_map_by_id;
  write_to_single_db(db, meta_map_by_id, infile, max_ldb_no);
  infile.close();
  cout << "write to single db: " << collection_sub_dir_str << endl;

  logging(log_file, meta_map_by_id, max_ldb_no);
  divide_to_multi_db(db, collection_sub_dir_str, meta_map_by_id, max_ldb_no, collectionDir, log_file);

  log_file.close();
  cout << "export done! detail: " << logStr << endl;
  return 0;
}
