#include <iostream>
#include "solution_2.3.15.h"

void exch(int* l, int i, int j) {
    int tmp = l[i];
    l[i] = l[j];
    l[j] = tmp;
}

int partitionWithV(int* l, int lo, int hi, int v) {
    int i = lo, j = hi + 1;
    while (1) {
        while (l[++i] < v)
            if (i == hi)
                break;
        while (l[--j] > v)
            if (j == lo)
                break;
        if (i >= j)
            break;
        exch(l, i, j);
    }
    exch(l, lo, j);
    return j;
}

int partition(int* l, int* ll, int lo, int hi) {
    int v = l[lo], i, j;
    if (ll[lo] != v){
        i = lo;
        while (ll[++i] != v);
        exch(ll, lo, i);
    }
    v = ll[lo];
    j = partitionWithV(l, lo, hi, v);
    v = l[j];
    j = partitionWithV(ll, lo, hi, v);
    return j;
}

void sort(int* l, int* ll, int lo, int hi) {
    if (lo >= hi)
        return;
    int j = partition(l, ll, lo, hi);
    sort(l, ll, lo, j - 1);
    sort(l, ll, j + 1, hi);
}

void NutsBoltsSort(int* l, int *ll, size_t len) {
    std::random_shuffle(&l[0], &l[len]);
    std::random_shuffle(&ll[0], &ll[len]);
    sort(l, ll, 0, len - 1);
}
