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
#include "leveldb/comparator.h"

using std::cerr;
using std::cout;
using std::endl;

namespace fs = boost::filesystem;

typedef std::map<int, std::pair<std::string, int> > MetaMapByIdType;
typedef MetaMapByIdType::value_type MetaMapByIdVtype;
typedef std::map<int, int> MetaMapByLrgType;
typedef MetaMapByLrgType::value_type MetaMapByLrgVtype;

const std::string ldbBaseDir("/tmp/test_file_to_multi_instance_leveldb");
const std::string logName("CURRENT");
const int maxDbSize = 400000;
const int perDbSize = maxDbSize / 2;

void logging(std::fstream& log_file, MetaMapByIdType& meta_map_by_id, const int& ldb_no, std::string action = "") {
  if (action != "") log_file << action << " ";
  log_file << ldb_no << " " << meta_map_by_id[ldb_no].first
           << " " << meta_map_by_id[ldb_no].second << endl;
}

void load_meta_from_log(MetaMapByIdType& meta_map_by_id, MetaMapByLrgType& meta_map_by_lrange, std::fstream& log_file) {
  std::char
  while () {
  }
}

int main(int argc, char** argv) {
  const std::string collection("global_activity");
  const std::string collectionDir(ldbBaseDir + "/" + collection);

  fs::path collection_path(collectionDir);
  if (!fs::exists(collection_path)) {
    cerr << collectionDir << " doesn't existed" << endl;
    return -1;
  }

  // TODO 加载meta info
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

  std::string ifile("data/global_activity1.csv");
  std::ifstream infile(ifile.c_str());
  if (!infile) {
    cerr << "error: unable to open file: "
         << ifile << endl;
    return -1;
  }

  infile.close();
  log_file.close();
  cout << "export done! detail: " << logStr << endl;
  return 0;
}
