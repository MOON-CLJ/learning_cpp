#include <assert.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "leveldb/db.h"
#include "leveldb/write_batch.h"
#include "leveldb/comparator.h"

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

int main() {
  leveldb::DB* db;
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status status = leveldb::DB::Open(options, "/tmp/test_file_to_single_instance_leveldb", &db);
  assert(status.ok());

  std::string ifile("data/global_activity.csv");
  std::ifstream infile(ifile.c_str());
  if (!infile) {
    cerr << "error: unable to open input file: "
         << ifile << endl;
    return -1;
  }

  std::string line, key;
  leveldb::WriteBatch batch;
  while (getline(infile, line)) {
    key = line.substr(0, line.find('\t'));
    batch.Put(key, line);
  }
  status = db->Write(leveldb::WriteOptions(), &batch);
  assert(status.ok());

  infile.close();
  delete db;

  return 0;
}
