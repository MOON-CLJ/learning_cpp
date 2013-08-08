#include <assert.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include "leveldb/db.h"
#include "leveldb/write_batch.h"
#include "leveldb/comparator.h"

using std::cerr;
using std::cout;
using std::endl;

namespace fs = boost::filesystem;

typedef std::map<int, std::pair<std::string, int> > MetaMapByIdType;
typedef MetaMapByIdType::value_type MetaMapByIdVtype;

int logging(std::fstream& log_file, MetaMapByIdType& meta_map_by_id, const int& ldb_no, std::string action = "") {
  if (action != "") log_file << action << " ";
  log_file << ldb_no << " " << meta_map_by_id[ldb_no].first << " " << meta_map_by_id[ldb_no].second << endl;
  return 0;
}

int divide_to_multi_db(leveldb::DB*& huge_db, std::string& huge_db_dir_str, MetaMapByIdType& meta_map_by_id, int& ldb_no, const leveldb::Options& options, const std::string& collection_dir_str, std::fstream& log_file) {
  const int max_db_size = 400000;
  const int per_db_size = max_db_size / 2;
  int huge_db_size = meta_map_by_id[ldb_no].second;
  int new_ldb_no = ldb_no; // TODO 目前默认ldb_no即为最大的no
  leveldb::Iterator* it = huge_db->NewIterator(leveldb::ReadOptions());
  it->SeekToFirst();

  if (huge_db_size <= max_db_size) return 0;
  while (huge_db_size > 0) {
    new_ldb_no++;
    std::string collection_sub_dir_str = collection_dir_str + "/" + boost::lexical_cast<std::string>(new_ldb_no);
    leveldb::DB* db;
    leveldb::Status status = leveldb::DB::Open(options, collection_sub_dir_str, &db);
    assert(status.ok());

    int i = 0;
    leveldb::WriteBatch batch;
    meta_map_by_id.insert(MetaMapByIdVtype(new_ldb_no, std::make_pair(it->key().ToString(), 0)));
    while (i < per_db_size && it->Valid()) {
      batch.Put(it->key(), it->value());
      it->Next();
      i++;
      meta_map_by_id[new_ldb_no].second++;
    }
    huge_db_size -= meta_map_by_id[new_ldb_no].second;
    status = db->Write(leveldb::WriteOptions(), &batch);
    assert(status.ok());
    delete db;

    // logging
    logging(log_file, meta_map_by_id, new_ldb_no);
  }

  // rm huge db dir
  fs::path huge_db_path(huge_db_dir_str);
  int rm_file_count = fs::remove_all(huge_db_path);
  assert(rm_file_count);
  logging(log_file, meta_map_by_id, ldb_no, "-");
  ldb_no = new_ldb_no;
  return 0;
}

bool init_dir(const fs::path& dir) {
  bool exists_if = fs::exists(dir);

  if (!exists_if) {
    bool create_status = fs::create_directory(dir);
    assert(create_status);
    cout << "create dir: " << dir.string() << endl;
  }

  return !exists_if;
}

int init_collection_current_log(const std::string& log_str) {
  std::string ofile(log_str);
  std::ofstream outfile(ofile.c_str());
  if (!outfile) {
    cerr << "error: unable to open output file: "
         << outfile << endl;
    return -1;
  } else {
    cout << "create collection log: " << ofile << endl;
    outfile.close();
    return 0;
  }
}

int loading_log(std::fstream& log_file, MetaMapByIdType& meta_map_by_id, int& max_ldb_no) {
  return 0;
}

int main(int argc, char** argv) {
  std::string ldb_base_dir_str("/tmp/test_file_to_multi_instance_leveldb");
  std::string current_collection_str("global_activity");
  std::string collection_dir_str(ldb_base_dir_str + "/" + current_collection_str);
  std::string log_name("CURRENT");
  std::string collection_current_log_str(collection_dir_str + "/" + log_name);

  fs::path ldb_base_dir(ldb_base_dir_str);
  init_dir(ldb_base_dir);

  fs::path collection_dir(collection_dir_str);
  if (init_dir(collection_dir)) {
    int init_log_status = init_collection_current_log(collection_current_log_str);
    assert((init_log_status == 0));
  }

  MetaMapByIdType meta_map_by_id;
  std::map<std::string, int> meta_map_by_lrange;
  std::fstream current_log_file(collection_current_log_str.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
  if (!current_log_file) {
    cerr << "error: unable to open current log file: "
         << collection_current_log_str << endl;
    return -1;
  }
  int max_ldb_no = 0;
  loading_log(current_log_file, meta_map_by_id, max_ldb_no);

  leveldb::Options options;
  options.create_if_missing = true;

  leveldb::DB* db;
  std::string collection_sub_dir_str = collection_dir_str + "/" + boost::lexical_cast<std::string>(++max_ldb_no);
  leveldb::Status status = leveldb::DB::Open(options, collection_sub_dir_str, &db);
  assert(status.ok());

  std::string ifile("data/global_activity.csv");
  std::ifstream infile(ifile.c_str());
  if (!infile) {
    cerr << "error: unable to open input file: "
         << ifile << endl;
    return -1;
  }

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
  status = db->Write(leveldb::WriteOptions(), &batch);
  assert(status.ok());

  // get the fisrt key
  leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
  it->SeekToFirst();
  meta_map_by_id[max_ldb_no].first = it->key().ToString();
  meta_map_by_lrange.insert(std::map<std::string, int>::value_type(it->key().ToString(), max_ldb_no));

  // write to log
  logging(current_log_file, meta_map_by_id, max_ldb_no);
  divide_to_multi_db(db, collection_sub_dir_str, meta_map_by_id, max_ldb_no, options, collection_dir_str, current_log_file);

  infile.close();
  current_log_file.close();
  delete db;

  return 0;
}
