#include <string>
#include <boost/lexical_cast.hpp>
#include "leveldb/db.h"

#include "comparators.h"

int NumericComparator::Compare(const leveldb::Slice& a, const leveldb::Slice& b) const {
  int a1, b1;
  a1 = boost::lexical_cast<int>(a.ToString());
  b1 = boost::lexical_cast<int>(b.ToString());
  if (a1 < b1) return -1;
  if (a1 > b1) return 1;

  return 0;
}

const char* NumericComparator::Name() const { return "NumericComparator"; }
void NumericComparator::FindShortestSeparator(std::string*, const leveldb::Slice&) const { }
void NumericComparator::FindShortSuccessor(std::string*) const { }
