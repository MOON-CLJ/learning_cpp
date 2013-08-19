#include <fstream>
#include <string>
#include <map>
#include <utility>

#include <boost/lexical_cast.hpp>
#include "leveldb/db.h"
#include "leveldb/write_batch.h"

#include "utils.h"
#include "comparators.h"
#include "constants.h"
#include "typedef.h"

using std::cerr;
using std::cout;
using std::endl;

void logging(std::fstream& log_file,
             MetaMapByIdType& meta_map_by_id,
             const int& ldb_no, std::string action) {
  if (action != "") log_file << action << " ";
  log_file << ldb_no << " " << meta_map_by_id[ldb_no].first
           << " " << meta_map_by_id[ldb_no].second << std::endl;
}

void destroy_large_db(std::fstream& log_file,
                      MetaMapByIdType& meta_map_by_id,
                      const int& ldb_no,
                      const std::string& collectionDir) {
  int large_db_size = meta_map_by_id[ldb_no].second;
  if (large_db_size <= maxDbSize) return;

  leveldb::Options options;
  std::string db_dir_str = collectionDir + "/" + boost::lexical_cast<std::string>(ldb_no);
  leveldb::Status status = leveldb::DestroyDB(db_dir_str, options);
  assert(status.ok());
  cout << "destroy db [ " << ldb_no << " ]" << endl;
  logging(log_file, meta_map_by_id, ldb_no, "-1");
}

void close_all_mapped_db(DbMapByIdType& db_map_by_id) {
  DbMapByIdType::iterator map_it = db_map_by_id.begin();
  while (map_it != db_map_by_id.end()) {
    delete map_it->second;
    ++map_it;
  }
}

int divide_to_multi_db(DbMapByIdType& db_map_by_id,
                       const int& ldb_no, int& max_ldb_no,
                       MetaMapByIdType& meta_map_by_id,
                       std::fstream& log_file,
                       const std::string& collectionDir,
                       const leveldb::Options& ldb_options) {
  leveldb::Iterator* it = db_map_by_id[ldb_no]->NewIterator(leveldb::ReadOptions());
  it->SeekToFirst();

  int large_db_size = meta_map_by_id[ldb_no].second;
  if (large_db_size <= maxDbSize) return -1;

  leveldb::Status status;
  while (it->Valid()) {
    leveldb::DB* db;
    std::string db_dir_str = collectionDir + "/" + boost::lexical_cast<std::string>(++max_ldb_no);
    status = leveldb::DB::Open(ldb_options, db_dir_str, &db);
    assert(status.ok());

    db_map_by_id.insert(DbMapByIdVtype(max_ldb_no, db));

    leveldb::WriteBatch batch;
    meta_map_by_id.insert(MetaMapByIdVtype(max_ldb_no, std::make_pair(it->key().ToString(), 0)));
    int i = 0;
    while (it->Valid() && i < perDbSize) {
      batch.Put(it->key(), it->value());
      it->Next();
      i++;
    }
    meta_map_by_id[max_ldb_no].second = i;
    status = db->Write(leveldb::WriteOptions(), &batch);
    assert(status.ok());
    cout << "divide db [ " << ldb_no << " ]" << " to db [ " << max_ldb_no << " ]" << endl;

    // logging
    logging(log_file, meta_map_by_id, max_ldb_no);
  }

  assert(it->status().ok());
  delete it;

  return 0;
}
