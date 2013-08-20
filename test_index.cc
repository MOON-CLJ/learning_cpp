#include <assert.h>
#include <iostream>
#include "leveldb/db.h"
#include "leveldb/cache.h"

#include "comparators.h"
#include "constants.h"

using std::cerr;
using std::cout;
using std::endl;

int main(int argc, char** argv) {
  MultiNumericComparator cmp;
  leveldb::Options options;
  options.write_buffer_size = 512 * 1048576;
  options.block_cache = leveldb::NewLRUCache(512 * 1048576);
  options.comparator = &cmp;
  options.create_if_missing = true;
  leveldb::DB* db;

  leveldb::Status status = leveldb::DB::Open(options, "/tmp/test_multi_ldb_exporter/global_activity/1/", &db);
  assert(status.ok());

  leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
  leveldb::Slice s_beg("8_^!");
  leveldb::Slice s_end("9_^!");
  for (it->Seek(s_beg); it->Valid() && cmp.Compare(it->key(), s_end) < 0; it->Next()) {
    cout << it->key().ToString() << ": "  << it->value().ToString() << endl;
  }
  assert(it->status().ok());
  delete it;
}
