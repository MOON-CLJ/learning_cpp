#include <algorithm>
#include "solution_2.2.20.h"

void merge(int* l, int* p, int* pp, int lo, int mid, int hi) {
    if (l[p[mid]] <= l[p[mid + 1]])
        return;
    int i, j, k;
    for (k = lo; k <= hi; k++)
        pp[k] = p[k];

    i = lo;
    j = mid + 1;
    for (k = lo; k <= hi; k++){
        if (i > mid)
            p[k] = pp[j++];
        else if (j > hi)
            p[k] = pp[i++];
        else if (l[pp[j]] < l[pp[i]])
            p[k] = pp[j++];
        else
            p[k] = pp[i++];
    }
}

int min(int x, int y) {
    if (x < y)
        return x;
    else
        return y;
}

void mergeSortBU(int* l, int* p, int* pp, size_t len) {
    int i, step;
    for (step = 1; step < len; step *= 2)
        for (i = 0; i < len - step; i += step * 2)
            merge(l, p, pp, i, i + step - 1, min(i + step * 2 - 1, len - 1));
}
