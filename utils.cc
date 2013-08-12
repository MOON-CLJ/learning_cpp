#include <fstream>
#include <string>
#include <map>
#include <utility>

#include "utils.h"
#include "constants.h"

void logging(std::fstream& log_file, MetaMapByIdType& meta_map_by_id, const int& ldb_no, std::string action) {
  if (action != "") log_file << action << " ";
  log_file << ldb_no << " " << meta_map_by_id[ldb_no].first
           << " " << meta_map_by_id[ldb_no].second << std::endl;
}
