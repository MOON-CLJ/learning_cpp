#ifndef UTILS_H_
#define UTILS_H_

#include <fstream>
#include <string>
#include <map>
#include <utility>

void logging(std::fstream&, std::map<int, std::pair<std::string, int> >&, const int&, std::string = "");

#endif
