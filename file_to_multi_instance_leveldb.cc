#include <assert.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "leveldb/db.h"
#include "leveldb/write_batch.h"
#include "leveldb/comparator.h"
#include "boost/filesystem.hpp"

using std::cerr;
using std::cout;
using std::endl;

std::string int2str(int number) {
  std::ostringstream ss;
  ss << number;
  return ss.str();
}

int str2int(const std::string &str) {
  std::istringstream ss(str);
  int n;
  ss >> n;
  return n;
}

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

void mk_dir_if(const std::string& dir) {
  cout << dir << endl;
  int mkdir_status = mkdir(dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  cout << mkdir_status << endl;
  cout << errno << endl;
}

int main(int argc, char** argv) {
  std::string ldb_base_dir = "/tmp/test_file_to_multi_instance_leveldb";
  std::string current_collection = "global_activity";
  std::vector<std::string> multi_instance_dirs;

  mk_dir_if(ldb_base_dir + "/" + current_collection);
  /*
  std::string multi_instance_ldb_base_dir = multi_instance_ldb_dir.substr(0, multi_instance_ldb_dir.rfind('/'));
  int mkdir_status = mkdir(multi_instance_ldb_base_dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

  // leveldb config
  leveldb::Options options;
  options.create_if_missing = true;

  leveldb::DB* db;
  leveldb::Status status = leveldb::DB::Open(options, multi_instance_ldb_dir, &db);
  assert(status.ok());

  std::string ifile("data/global_activity.csv");
  std::ifstream infile(ifile.c_str());
  if (!infile) {
    cerr << "error: unable to open input file: "
         << ifile << endl;
    return -1;
  }

  std::string line, key, value;
  int delimiter_idx;
  leveldb::WriteBatch batch;
  while (getline(infile, line)) {
    delimiter_idx = line.find('\t');
    key = line.substr(0, delimiter_idx);
    value = line.substr(delimiter_idx + 1);
    batch.Put(key, value);
    break;
  }
  status = db->Write(leveldb::WriteOptions(), &batch);
  assert(status.ok());

  divide_to_multi_db(db);
  infile.close();
  delete db;
  */

  return 0;
}
