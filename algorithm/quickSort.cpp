#include <iostream>
#include "quickSort.h"

void exch(int* l, int i, int j) {
    int tmp = l[i];
    l[i] = l[j];
    l[j] = tmp;
}

int partition(int* l, int lo, int hi) {
    int i = lo, j = hi + 1, tmp;
    int v = l[lo];
    while (1) {
        while (l[++i] < v) {
            if (i == hi)
                break;
        }
        while (l[--j] > v) {
            if (j == lo)
                break;
        }
        if (i >= j)
            break;
        exch(l, i, j);
    }
    exch(l, lo, j);
    return j;
}

void sort(int* l, int lo, int hi) {
    if (lo >= hi)
        return;
    int j = partition(l, lo, hi);
    sort(l, lo, j - 1);
    sort(l, j + 1, hi);
}

void quickSort(int* l, size_t len) {
    std::random_shuffle(&l[0], &l[len]);
    sort(l, 0, len - 1);
}
