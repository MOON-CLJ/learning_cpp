#include <string>
#include <boost/lexical_cast.hpp>
#include "leveldb/db.h"

#include "comparators.h"

int NumericComparator::Compare(const leveldb::Slice& a, const leveldb::Slice& b) const {
  size_t a_len, b_len;
  a_len = a.size();
  b_len = b.size();
  if (a_len < b_len) return -1;
  if (a_len > b_len) return 1;
  return a.compare(b);
}

const char* NumericComparator::Name() const { return "NumericComparator"; }
void NumericComparator::FindShortestSeparator(std::string*, const leveldb::Slice&) const { }
void NumericComparator::FindShortSuccessor(std::string*) const { }
