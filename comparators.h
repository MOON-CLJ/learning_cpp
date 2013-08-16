#ifndef COMPARATORS_H_
#define COMPARATORS_H_

#include <string>
#include "leveldb/db.h"
#include "leveldb/comparator.h"

class NumericComparator : public leveldb::Comparator {
 public:
  // Three-way comparison function:
  //   if a < b: negative result
  //   if a > b: positive result
  //   else: zero result
  int Compare(const leveldb::Slice&, const leveldb::Slice&) const;

  // Ignore the following methods for now:
  const char* Name() const;
  void FindShortestSeparator(std::string*, const leveldb::Slice&) const;
  void FindShortSuccessor(std::string*) const;
};

class MultiNumericComparator : public leveldb::Comparator {
 public:
  // Three-way comparison function:
  //   if a < b: negative result
  //   if a > b: positive result
  //   else: zero result
  int Compare(const leveldb::Slice&, const leveldb::Slice&) const;

  // Ignore the following methods for now:
  const char* Name() const;
  void FindShortestSeparator(std::string*, const leveldb::Slice&) const;
  void FindShortSuccessor(std::string*) const;
};

struct NumericMapComp {
  bool operator() (const std::string&, const std::string&) const;
};

#endif
