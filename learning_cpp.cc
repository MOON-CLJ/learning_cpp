#include <iostream>

/*
int main()
{
    int sum = 0, value;
    while (std::cin >> value)
        sum += value;
    std::cout << sum << std::endl;
    return 0;
}
*/

/*
class Foo {
};

int main() {
    return 0;
}
*/

/*
void printValues(int (&arr)[10]) {
  return;
}

int main() {
  int k[10] = {0,1,2,3,4,5,6,7,8,9};
  printValues(k);
  return 0;
}
*/

#include <map>
#include <string>

#include "comparators.h"

int main() {
  std::map<std::string, int, NumericMapComp> count;
  count.insert(std::map<std::string, int, NumericMapComp>::value_type("1", 1));
  count.insert(std::map<std::string, int, NumericMapComp>::value_type("11", 11));
  count.insert(std::map<std::string, int, NumericMapComp>::value_type("2", 2));
  std::map<std::string, int, NumericMapComp>::iterator map_it = count.begin();
  while (map_it != count.end()) {
    std::cout << map_it->first << " | " << map_it->second << std::endl;
    ++map_it;
  }
  return 0;
}
