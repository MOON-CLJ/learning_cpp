#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <utility>

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

typedef std::map<int, leveldb::DB*> DbMapByIdType;
typedef DbMapByIdType::value_type DbMapByIdVtype;

void load_meta_from_log(MetaMapByIdType& meta_map_by_id, MetaMapByLrgType& meta_map_by_lrange, std::fstream& log_file) {
  int ldb_no, count;
  std::string lrange;

  while (getline(log_file, line)) {
    istringstream stream(line);
    stream >> ldb_no;
    if (ldb_no == -1) {
      stream >> ldb_no >> lrange;
      meta_map_by_id.erase(ldb_no);
      meta_map_by_lrange.erase(lrange);
    } else {
      stream >> lrange >> count;
      meta_map_by_id.insert(MetaMapByIdVtype(ldb_no, std::make_pair(lrange, count)));
      meta_map_by_lrange.insert(MetaMapByLrgVtype(lrange, ldb_no));
    }
  }
}

void load_multi_db(DbMapByIdType& db_map_by_id, const MetaMapByIdType& meta_map_by_id, const std::string& collectionDir) {
  MetaMapByIdType::iterator map_it = meta_map_by_id.begin();
  int ldb_no;
  leveldb::Status status;
  while (map_it != meta_map_by_id.end()) {
    ldb_no = map_it->first;
    leveldb::DB* db;
    std::string collection_sub_dir_str = collectionDir + "/" + boost::lexical_cast<std::string>(ldb_no);
    status = leveldb::DB::Open(options, collection_sub_dir_str, &db);
    assert(status.ok());

    db_map_by_id.insert(DbMapByIdVtype(ldb_no, db));
  }
}

void close_multi_db(DbMapByIdType& db_map_by_id) {
  DbMapByIdType::iterator map_it = db_map_by_id.begin();
  while (map_it != db_map_by_id.end()) {
    delete map_it->second;
  }
}

void update_to_multi_db(DbMapByIdType& db_map_by_id, MetaMapByIdType& meta_map_by_id, const MetaMapByLrgVtype& meta_map_by_lrange, std::ifstream& infile) {
  update_meta_map(meta_map_by_id);
}

void update_meta_map(const MetaMapByIdType& meta_map_by_id) {
}

int main(int argc, char** argv) {
  const std::string collection("global_activity");
  const std::string collectionDir(ldbBaseDir + "/" + collection);

  fs::path collection_path(collectionDir);
  if (!fs::exists(collection_path)) {
    cerr << collectionDir << " doesn't existed" << endl;
    return -1;
  }

  const std::string logStr(collectionDir + "/" + logName);
  std::fstream log_file(logStr.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
  if (!log_file) {
    cerr << "error: unable to open log: "
         << logStr << endl;
    return -1;
  }

  MetaMapByIdType meta_map_by_id;
  MetaMapByLrgType meta_map_by_lrange;
  load_meta_from_log(meta_map_by_id, meta_map_by_lrange, log_file);
  DbMapByIdType db_map_by_id;
  load_multi_db(db_map_by_id, meta_map_by_id, collectionDir);

  std::string ifile("data/global_activity.csv");
  std::ifstream infile(ifile.c_str());
  if (!infile) {
    cerr << "error: unable to open file: "
         << ifile << endl;
    return -1;
  }

  update_to_multi_db(db_map_by_id, meta_map_by_lrange, infile);

  close_multi_db(db_map_by_id);
  infile.close();
  log_file.close();
  cout << "export done! detail: " << logStr << endl;
  return 0;
}
