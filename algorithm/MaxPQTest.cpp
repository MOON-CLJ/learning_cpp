#include "MaxPQ.h"

int main() {
    int i;
    int a[] = {3, 2, 1, 7, 6, 5, 9, 4, 10, 8};

    MaxPQ<int> pq(10);
    for (i = 0; i < 10; i++)
        pq.insert(a[i]);

    for (i = 0; i < 10; i++)
        std::cout << pq.delMax() << std::endl;

    return 0;
}
