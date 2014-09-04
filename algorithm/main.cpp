#include <iostream>
#include "mergeSort.h"

int main() {
    int a[] = {6, 3, 1, 5, 2, 8, 7, 10, 11};
    int i;
    size_t len = sizeof(a) / sizeof(*a);
    int aux[len];
    mergeSort(a, aux, 0, len - 1);
    for (i = 0; i < len; i++)
        std::cout << a[i] << std::endl;
    return 0;
}
