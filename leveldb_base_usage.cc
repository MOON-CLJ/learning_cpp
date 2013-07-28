#include <assert.h>
#include <iostream>
#include <sstream>
#include "leveldb/db.h"
#include "leveldb/write_batch.h"

std::string convertInt(int number) {
  std::stringstream ss;
  ss << number;
  return ss.str();
}

int main() {
  leveldb::DB* db;
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status status = leveldb::DB::Open(options, "/tmp/test_write_size_db", &db);
  assert(status.ok());

  leveldb::WriteBatch batch;
  std::string key;
  for (unsigned int i = 0; i < 20; ++i) {
    key = convertInt(i);
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
