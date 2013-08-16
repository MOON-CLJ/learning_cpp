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

int MultiNumericComparator::Compare(const leveldb::Slice& a, const leveldb::Slice& b) const {
  // TODO
  return 0;
}

const char* MultiNumericComparator::Name() const { return "MultiNumericComparator"; }
void MultiNumericComparator::FindShortestSeparator(std::string*, const leveldb::Slice&) const { }
void MultiNumericComparator::FindShortSuccessor(std::string*) const { }

bool NumericMapComp::operator() (const std::string& k1, const std::string& k2) const {
  std::string::size_type k1_len, k2_len;
  k1_len = k1.size();
  k2_len = k2.size();
  if (k1_len < k2_len) return true;
  if (k1_len > k2_len) return false;
  return (k1 < k2);
}
