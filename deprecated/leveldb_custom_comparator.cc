#include <assert.h>
#include <iostream>
#include <sstream>
#include <string>
#include "leveldb/db.h"
#include "leveldb/write_batch.h"
#include "leveldb/comparator.h"

std::string int2str(int number) {
  std::stringstream ss;
  ss << number;
  return ss.str();
}

int str2int(const std::string &str) {
  std::stringstream ss(str);
  int n;
  ss >> n;
  return n;
}

class IntComparator : public leveldb::Comparator {
 public:
  // Three-way comparison function:
  //   if a < b: negative result
  //   if a > b: positive result
  //   else: zero result
  int Compare(const leveldb::Slice& a, const leveldb::Slice& b) const {
    int a1, b1;
    a1 = str2int(a.ToString());
    b1 = str2int(b.ToString());
    if (a1 < b1) return -1;
    if (a1 > b1) return +1;
    return 0;
  }

  // Ignore the following methods for now:
  const char* Name() const { return "IntComparator"; }
  void FindShortestSeparator(std::string*, const leveldb::Slice&) const { }
  void FindShortSuccessor(std::string*) const { }
};

int main() {
  IntComparator cmp;
  leveldb::DB* db;
  leveldb::Options options;
  options.create_if_missing = true;
  options.comparator = &cmp;
  leveldb::Status status = leveldb::DB::Open(options, "/tmp/test_custom_comparator_db", &db);
  assert(status.ok());

  leveldb::WriteBatch batch;
  std::string key;
  for (unsigned int i = 0; i < 20; ++i) {
      key = int2str(i);
      batch.Put(key, key);
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
