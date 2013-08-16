#ifndef TYPEDEF_H_
#define TYPEDEF_H_

#include <map>
#include <utility>

#include "leveldb/db.h"

#include "comparators.h"

typedef std::map<int, std::pair<std::string, int> > MetaMapByIdType;
typedef MetaMapByIdType::value_type MetaMapByIdVtype;
typedef std::map<std::string, int, NumericMapComp> MetaMapByLrgType;
typedef MetaMapByLrgType::value_type MetaMapByLrgVtype;

typedef std::map<int, leveldb::DB*> DbMapByIdType;
typedef DbMapByIdType::value_type DbMapByIdVtype;
typedef std::map<int, leveldb::WriteBatch> BatchMapByIdType;
typedef BatchMapByIdType::value_type BatchMapByIdVtype;

#endif
