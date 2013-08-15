#ifndef UTILS_H_
#define UTILS_H_

#include <fstream>
#include <string>
#include <map>
#include <utility>

#include "leveldb/db.h"

#include "constants.h"

void logging(std::fstream&, MetaMapByIdType&, const int&, std::string = "");
void destroy_large_db(std::fstream&, MetaMapByIdType&, const int&, const std::string&);
void close_all_mapped_db(DbMapByIdType&);
int divide_to_multi_db(DbMapByIdType&, const int&, int&, MetaMapByIdType&, std::fstream&, const std::string&, const leveldb::Options&);

#endif
