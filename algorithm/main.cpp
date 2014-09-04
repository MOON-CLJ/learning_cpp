#include <iostream>
#include <algorithm>
#include "mergeSortBU.h"

int main() {
    int i;
    size_t len = 200201;
    int a[len];
    for (i = 0; i < len; i++)
        a[i] = i;
    std::random_shuffle(&a[0], &a[len]);
    int aux[len];
    int * l = (int *) a;
    int * ll = (int *) aux;
    mergeSort(l, ll, len);
    for (i = 0; i < len; i++)
        if (a[i] != i)
            std::cout << a[i] << std::endl;

    return 0;
}
