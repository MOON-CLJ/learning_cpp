#include <iostream>

#include "FixedCapacityStackOfStrings.h"

int main() {
    fixedCapacityStackOfStrings stack(4);
    std::string str[17] = {"it", "was", "-", "the", "best", "-", "of", "times", "-",
        "-", "-", "it", "was", "-", "the", "-", "-"};
    std::vector<std::string> svec(str, str + 17);
    std::string mstr("-");
    for (std::vector<std::string>::iterator iter = svec.begin(); iter < svec.end(); iter++) {
        if (mstr.compare(*iter) == 0)
            std::cout << stack.pop() << std::endl;
        else
            stack.push(*iter);
    }
    return 0;
}
