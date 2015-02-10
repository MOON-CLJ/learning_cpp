#include <iostream>
#include "solution_2.4.35.h"


int main() {
    const size_t len = 4;
    int p[len] = {1000, 100, 10, 1};
    Sample<int> sample(len, p);
    std::cout << sample.random() << std::endl;
    sample.change(3, 2);
    std::cout << sample.random() << std::endl;
    return 0;
}
