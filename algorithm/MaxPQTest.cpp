#include "MaxPQ.h"

int main() {
    size_t i;
    size_t size = 10;
    int a[] = {3, 2, 1, 7, 6, 5, 9, 4, 10, 8};

    MaxPQ<int> pq(2);
    for (i = 0; i < size; i++)
        pq.insert(a[i]);

    for (i = 0; i < size; i++) 
        std::cout << pq.delMax() << std::endl;

    return 0;
}
