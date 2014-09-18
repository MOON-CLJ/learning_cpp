#include <iostream>
#include "quickSort.h"

void exch(int* l, int i, int j) {
    int tmp = l[i];
    l[i] = l[j];
    l[j] = tmp;
}

std::pair<int, int> partition(int* l, int lo, int hi) {
    int i = lo + 1, j = hi, p, q, k;
    p = i;
    q = j;
    int v = l[lo];
    while (1) {
        while (i <= q && l[i] <= v) {
            if (l[i] == v) {
                if (i == p) {
                    i++;
                    p++;
                }
                else
                    exch(l, i, p++);
            }
            else
                i++;
        }
        while (j >= p && l[j] >= v) {
            if (l[j] == v) {
                if (j == q) {
                    j--;
                    q--;
                }
                else
                    exch(l, j, q--);
            }
            else
                j--;
        }
        if (i > j)
            break;
        exch(l, i++, j--);
    }
    for (k = p; k <= j; k++)
        exch(l, k, k - (p - lo));
    for (k = q; k >= i; k--)
        exch(l, k, k + (hi - q));
    return std::make_pair(j - (p - lo), i + (hi - q));
}

void sort(int* l, int lo, int hi) {
    if (lo >= hi)
        return;
    std::pair<int, int> delim = partition(l, lo, hi);
    sort(l, lo, delim.first);
    sort(l, delim.second, hi);
}

void quickSort(int* l, size_t len) {
    std::random_shuffle(&l[0], &l[len]);
    sort(l, 0, len - 1);
}
