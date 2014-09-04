#include <iostream>
#include "mergeSortBU.h"

int main() {
    int a[] = {6, 3, 1, 5, 2};
    int i;
    size_t len = sizeof(a) / sizeof(*a);
    int aux[len];
    int * l = (int *) a;
    int * ll = (int *) aux;
    mergeSort(l, ll, len);
    for (i = 0; i < len; i++)
        std::cout << a[i] << std::endl;

    return 0;
}
