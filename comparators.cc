#include <string>
#include <boost/lexical_cast.hpp>
#include "leveldb/db.h"

#include "comparators.h"

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
  int a_size, b_size;
  a_size = a.size();
  b_size = b.size();
  const char* a_data = a.data();
  const char* b_data = b.data();
  while (a_size) {
    std::string a_tmp_s, b_tmp_s;
    while (a_size && *a_data != '_') {
      a_tmp_s += *a_data;
      ++a_data;
      --a_size;
    }
    while (b_size && *b_data != '_') {
      b_tmp_s += *b_data;
      ++b_data;
      --b_size;
    }

    // deal with "^ $"
    if (a_tmp_s == "^" || b_tmp_s == "$") return -1;
    if (a_tmp_s == "$" || b_tmp_s == "^") return 1;

    int a_tmp_i, b_tmp_i;
    a_tmp_i = boost::lexical_cast<int>(a_tmp_s);
    b_tmp_i = boost::lexical_cast<int>(b_tmp_s);

    if (a_tmp_i < b_tmp_i) return -1;
    if (a_tmp_i > b_tmp_i) return 1;

    if (a_size) {
      ++a_data;
      --a_size;
      ++b_data;
      --b_size;
    }
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
