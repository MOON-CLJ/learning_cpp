#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <string>
#include <map>
#include <utility>

#include "leveldb/db.h"

const std::string ldbBaseDir("/tmp/test_file_to_multi_instance_leveldb");
const std::string logName("CURRENT");
const int maxDbSize = 400000;
const int perDbSize = maxDbSize / 2;

typedef std::map<int, std::pair<std::string, int> > MetaMapByIdType;
typedef MetaMapByIdType::value_type MetaMapByIdVtype;
typedef std::map<std::string, int> MetaMapByLrgType;
typedef MetaMapByLrgType::value_type MetaMapByLrgVtype;

typedef std::map<int, leveldb::DB*> DbMapByIdType;
typedef DbMapByIdType::value_type DbMapByIdVtype;
typedef std::map<int, leveldb::WriteBatch> BatchMapByIdType;
typedef BatchMapByIdType::value_type BatchMapByIdVtype;

#endif
