#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>

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

void write_to_single_db(DbMapByIdType& db_map_by_id, MetaMapByIdType& meta_map_by_id, std::ifstream& infile, const int& ldb_no, const std::string& collectionDir) {
  NumericComparator cmp;
  leveldb::Options options;
  options.comparator = &cmp;
  options.create_if_missing = true;

  leveldb::DB* db;
  {
    std::string db_dir_str = collectionDir + "/" + boost::lexical_cast<std::string>(ldb_no);
    leveldb::Status status = leveldb::DB::Open(options, db_dir_str, &db);
    assert(status.ok());
  }

  db_map_by_id.insert(DbMapByIdVtype(ldb_no, db));
  meta_map_by_id.insert(MetaMapByIdVtype(ldb_no, std::make_pair("", 0)));

  std::string line, key, value;
  int delimiter_idx;
  leveldb::WriteBatch batch;
  while (getline(infile, line)) {
    delimiter_idx = line.find('\t');
    key = line.substr(0, delimiter_idx);
    value = line.substr(delimiter_idx + 1);
    batch.Put(key, value);
    meta_map_by_id[ldb_no].second++;
  }
  leveldb::Status status = db_map_by_id[ldb_no]->Write(leveldb::WriteOptions(), &batch);
  assert(status.ok());

  // get the fisrt key
  leveldb::Iterator* it = db_map_by_id[ldb_no]->NewIterator(leveldb::ReadOptions());
  it->SeekToFirst();
  meta_map_by_id[ldb_no].first = it->key().ToString();
  int i = 0;
  while (it->Valid() && i < 10) {
    cout << it->key().ToString() << endl;
    it->Next();
    i++;
  }

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

  std::string ifile("data/global_activity.csv");
  std::ifstream infile(ifile.c_str());
  if (!infile) {
    cerr << "error: unable to open file: "
         << ifile << endl;
    return -1;
  }

  int max_ldb_no = 1;
  DbMapByIdType db_map_by_id;
  MetaMapByIdType meta_map_by_id;
  write_to_single_db(db_map_by_id, meta_map_by_id, infile, max_ldb_no, collectionDir);

  cout << "hehe" << endl;
  leveldb::Iterator* it = db_map_by_id[max_ldb_no]->NewIterator(leveldb::ReadOptions());
  it->SeekToFirst();
  int i = 0;
  while (it->Valid() && i < 10) {
    cout << it->key().ToString() << endl;
    it->Next();
    i++;
  }
  cout << "hehe" << endl;

  infile.close();
  cout << "write to db [ " << max_ldb_no << " ]" << endl;
  logging(log_file, meta_map_by_id, max_ldb_no);

  int old_max_ldb_no = max_ldb_no;
  divide_to_multi_db(db_map_by_id, max_ldb_no, meta_map_by_id, log_file, collectionDir);
  close_all_mapped_db(db_map_by_id);
  destroy_large_db(log_file, meta_map_by_id, old_max_ldb_no, collectionDir);

  log_file.close();
  cout << "export done! detail: " << logStr << endl;
  return 0;
}
