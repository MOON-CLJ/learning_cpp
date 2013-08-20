#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <string>

const std::string ldbBaseDir("/tmp/test_multi_ldb_exporter");
const std::string logName("CURRENT");
const int maxDbSize = 10000000;
const int perDbSize = maxDbSize / 2;

const char idxTerminated = '!';
const char idxLower = '^';
const char idxUpper = '$';

// tmp
const std::string origin_ifile_str("data/fake_data4_origin.csv");
const std::string update_ifile_str("data/fake_data1_update.csv");

#endif
