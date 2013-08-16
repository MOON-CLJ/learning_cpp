#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <string>

const std::string ldbBaseDir("/tmp/test_file_to_multi_instance_leveldb");
const std::string logName("CURRENT");
const int maxDbSize = 500000;
const int perDbSize = maxDbSize / 2;

#endif
