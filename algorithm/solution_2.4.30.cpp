#include <iostream>

#include "solution_2.4.30.h"

int main() {
    int i;
    MedianPQ<int> pq(10);
    for (i = 0; i < 10; i++)
        pq.insert(i);
    pq.print();
    while (!pq.isEmpty()) {
        std::cout << pq.delMedian() << std::endl;
        pq.print();
    }
    return 0;
}
