#include <string>
#include <boost/lexical_cast.hpp>
#include "leveldb/db.h"

#include "comparators.h"
#include "constants.h"

int NumericComparator::Compare(const leveldb::Slice& a, const leveldb::Slice& b) const {
  // Notice: 没考虑负数，也没考虑小数
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
  const char* a_data = a.data();
  const char* b_data = b.data();
  char* a_data_next;
  char* b_data_next;

  while (1) {
    if (*a_data == idxLower || *b_data == idxUpper) return -1;
    if (*a_data == idxUpper || *b_data == idxLower) return 1;

    double d1, d2;
    d1 = strtod(a_data, &a_data_next);
    d2 = strtod(b_data, &b_data_next);

    if (d1 < d2) return -1;
    if (d1 > d2) return 1;

    if (*a_data_next == idxTerminated) break;
    a_data = ++a_data_next;
    b_data = ++b_data_next;
  }

  return 0;
}

const char* MultiNumericComparator::Name() const { return "MultiNumericComparator"; }
void MultiNumericComparator::FindShortestSeparator(std::string*, const leveldb::Slice&) const { }
void MultiNumericComparator::FindShortSuccessor(std::string*) const { }

bool NumericMapComp::operator() (const std::string& k1, const std::string& k2) const {
  // Notice: 没考虑负数，也没考虑小数
  std::string::size_type k1_len, k2_len;
  k1_len = k1.size();
  k2_len = k2.size();
  if (k1_len < k2_len) return true;
  if (k1_len > k2_len) return false;
  return (k1 < k2);
}
