#include <iostream>
#include "quickSort.h"

void exch(int* l, int i, int j) {
    int tmp = l[i];
    l[i] = l[j];
    l[j] = tmp;
}

void prepare_median(int * l, int lo, int hi) {
    int i = (lo + hi) / 2;
    if (l[lo] < l[i])
        exch(l, lo, i);
    if (l[lo] > l[hi])
        exch(l, lo, hi);
    if (l[lo] < l[i])
        exch(l, lo, i);
    if (lo + 1 < i)
        exch(l, lo + 1, i);
}

int partition(int* l, int lo, int hi) {
    prepare_median(l, lo, hi);
    int i = lo + 1, j = hi;
    int v = l[lo];
    while (1) {
        while (l[++i] < v);
        while (l[--j] > v);
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
