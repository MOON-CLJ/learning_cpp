#include <iostream>
#include <algorithm>
#include "mergeSortBU.h"
#include "selectionSort.h"
#include "solution_2.2.16.h"

/*
int main() {
    // mergeSortBU.cpp
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

int main() {
    // selectionSort.cpp
    int a[] = {6, 3, 1, 5, 2, 8, 7, 10, 11};
    int i;
    size_t len = sizeof(a) / sizeof(*a);
    selectionSort(a, len);
    for (i = 0; i < len; i++)
        std::cout << a[i] << std::endl;
    return 0;
}
*/

int main() {
    // solution_2.2.16.cpp
    int i;
    size_t len = 16161;
    int a[len];
    for (i = 0; i < len; i++)
        a[i] = i;
    std::random_shuffle(&a[0], &a[len]);
    int aux[len];
    mergeSortBU1(a, aux, len);
    for (i = 0; i < len; i++)
        if (a[i] != i)
            std::cout << a[i] << std::endl;

    return 0;
}
