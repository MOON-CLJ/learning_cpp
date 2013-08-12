#include <fstream>
#include <string>
#include <map>
#include <utility>

#include "utils.h"

void logging(std::fstream& log_file, std::map<int, std::pair<std::string, int> >& meta_map_by_id, const int& ldb_no, std::string action) {
  if (action != "") log_file << action << " ";
  log_file << ldb_no << " " << meta_map_by_id[ldb_no].first
           << " " << meta_map_by_id[ldb_no].second << std::endl;
}
