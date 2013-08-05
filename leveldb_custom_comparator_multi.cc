#include <assert.h>
#include <iostream>
#include <sstream>
#include <string>
#include "leveldb/db.h"
#include "leveldb/write_batch.h"
#include "leveldb/comparator.h"

std::string int2str(int number) {
  std::istringstream ss;
  ss << number;
  return ss.str();
}

int str2int(const std::string &str) {
  std::ostringstream ss(str);
  int n;
  ss >> n;
  return n;
}

void ParseKey(const leveldb::Slice& slc, int& a1, int& a2) {
  std::string ss = slc.ToString();
  std::string delimiter = "_";
  size_t post = ss.find(delimiter);
  a1 = str2int(ss.substr(0, post));
  a2 = str2int(ss.substr(post + 1));
  return;
}

class MultiPartIntComparator : public leveldb::Comparator {
 public:
  // Three-way comparison function:
  //   if a < b: negative result
  //   if a > b: positive result
  //   else: zero result
  int Compare(const leveldb::Slice& a, const leveldb::Slice& b) const {
    int a1, a2, b1, b2;
    ParseKey(a, a1, a2);
    ParseKey(b, b1, b2);
    if (a1 < b1) return -1;
    if (a1 > b1) return +1;
    if (a2 < b2) return -1;
    if (a2 > b2) return +1;

    return 0;
  }

  // Ignore the following methods for now:
  const char* Name() const { return "MultiPartIntComparator"; }
  void FindShortestSeparator(std::string*, const leveldb::Slice&) const { }
  void FindShortSuccessor(std::string*) const { }
};

int main() {
  MultiPartIntComparator cmp;
  leveldb::DB* db;
  leveldb::Options options;
  options.create_if_missing = true;
  options.comparator = &cmp;
  leveldb::Status status = leveldb::DB::Open(options, "/tmp/test_custom_comparator_multi_db", &db);
  assert(status.ok());

  leveldb::WriteBatch batch;
  std::string key1;
  std::string key2;
  for (unsigned int i = 0; i < 2; ++i)
    for (unsigned int j = 0; j < 20; ++j) {
      key1 = int2str(i);
      key2 = int2str(j);
      batch.Put(key1 + "_" + key2, key2);
  }

  status = db->Write(leveldb::WriteOptions(), &batch);

  leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());

  for (it->SeekToFirst(); it->Valid(); it->Next())
  {
      std::cout << it->key().ToString() << " : " << it->value().ToString() << std::endl;
  }

  delete db;
  return 0;
}
