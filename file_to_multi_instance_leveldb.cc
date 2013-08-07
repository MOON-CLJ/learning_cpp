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

int divide_to_multi_db(leveldb::DB*& db) {
  // const params
  const int single_instance_size = 200000;
  leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());

  for (it->SeekToFirst(); it->Valid(); it->Next())
  {
      std::cout << it->key().ToString() << " : " << it->value().ToString() << std::endl;
  }

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

int loading_log(std::map<int, std::pair<std::string, int> >& no_range_map, std::fstream& log_file, int& max_ldb_no) {
  return 0;
}

int logging(std::fstream& log_file, std::map<int, std::pair<std::string, int> >& no_range_map, int& ldb_no) {
  log_file << ldb_no << " " << no_range_map[ldb_no].first << " " << no_range_map[ldb_no].second << endl;
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

  std::map<int, std::pair<std::string, int> > multi_ldb_no_range_map;
  std::fstream current_log_file(collection_current_log_str.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
  if (!current_log_file) {
    cerr << "error: unable to open current log file: "
         << collection_current_log_str << endl;
    return -1;
  }
  int max_ldb_no = 0;
  loading_log(multi_ldb_no_range_map, current_log_file, max_ldb_no);

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

  typedef std::map<int, std::pair<std::string, int> >::value_type multi_ldb_no_range_map_vtype;
  multi_ldb_no_range_map.insert(multi_ldb_no_range_map_vtype(max_ldb_no, std::make_pair("", 0)));

  std::string line, key, value;
  int delimiter_idx;
  leveldb::WriteBatch batch;
  while (getline(infile, line)) {
    delimiter_idx = line.find('\t');
    key = line.substr(0, delimiter_idx);
    value = line.substr(delimiter_idx + 1);
    batch.Put(key, value);
    multi_ldb_no_range_map[max_ldb_no].second++;
    break;
  }
  status = db->Write(leveldb::WriteOptions(), &batch);
  assert(status.ok());

  // get the fisrt key
  leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
  it->SeekToFirst();
  multi_ldb_no_range_map[max_ldb_no].first = it->key().ToString();

  // write to log
  logging(current_log_file, multi_ldb_no_range_map, max_ldb_no);
  divide_to_multi_db(db);

  infile.close();
  current_log_file.close();
  delete db;

  return 0;
}
