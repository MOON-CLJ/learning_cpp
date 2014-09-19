#include <iostream>
#include "quickSort.h"

void exch(int* l, int i, int j) {
    int tmp = l[i];
    l[i] = l[j];
    l[j] = tmp;
}

int partition(int* l, int lo, int hi) {
    int i = lo, j = hi + 1;
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

void insertionSort(int* l, int lo, int hi) {
    if (lo >= hi)
        return;
    int i, j, min, tmp;
    for (i = lo + 1; i <= hi; i++) {
        min = i;
        for (j = i - 1; j >= lo && l[j] > l[i]; j--)
            min = j;
        tmp = l[i];
        for (j = i; j > min; j--)
            l[j] = l[j - 1];
        l[min] = tmp;
    }
}

void sort(int* l, int lo, int hi, int M) {
    if (lo + M >= hi) {
        insertionSort(l, lo, hi);
        return;
    }
    int j = partition(l, lo, hi);
    sort(l, lo, j - 1, M);
    sort(l, j + 1, hi, M);
}

void quickSort(int* l, size_t len) {
    std::random_shuffle(&l[0], &l[len]);
    int i, max=0;
    for (i = 1; i < len; i++)
        if (l[i] > l[max])
            max = i;
    if (max != len - 1)
        exch(l, max, len - 1);
    sort(l, 0, len - 1, 3);
}
