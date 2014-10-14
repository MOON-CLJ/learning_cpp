#include <iostream>

#include "FixedCapacityStackOfStrings.h"

int main() {
    fixedCapacityStackOfStrings stack(4);
    std::cout << stack.size() << std::endl;
    std::cout << stack.isEmpty() << std::endl;
    return 0;
}
