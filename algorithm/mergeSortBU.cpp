#include "mergeSortBU.h"

void merge(int* l, int* ll, int lo, int mid, int hi) {
    int i, j, k;

    i = lo;
    j = mid + 1;
    for (k = lo; k <= hi; k++){
        if (i > mid)
            ll[k] = l[j++];
        else if (j > hi)
            ll[k] = l[i++];
        else if (l[j] < l[i])
            ll[k] = l[j++];
        else
            ll[k] = l[i++];
    }
}

int min(int x, int y) {
    if (x < y)
        return x;
    else
        return y;
}

void mergeSort(int*& l, int*& ll, size_t len) {
    int i, step, cnt = 0;
    int * tmp;
    for (step = 1; step < len; step *= 2) {
        for (i = 0; i < len; i += step * 2)
            merge(l, ll, i, i + step - 1, min(i + step * 2 - 1, len - 1));
        tmp = l;
        l = ll;
        ll = tmp;
        cnt += 1;
    }
    if (cnt % 2 == 1) {
        tmp = l;
        l = ll;
        ll = tmp;
    }
}
