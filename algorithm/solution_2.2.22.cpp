#include "solution_2.2.22.h"

int min(int* ll, int x, int y, int z, int lo, int mid1, int mid2, int hi) {
    int tmp = -1;
    if (lo <= x && x <= mid1) {
        if (tmp == -1 || ll[x] < ll[tmp])
            tmp = x;
    }
    if (mid1 < y && y <= mid2) {
        if (tmp == -1 || ll[y] < ll[tmp])
            tmp = y;
    }
    if (mid2 < z && z <= hi) {
        if (tmp == -1 || ll[z] < ll[tmp])
            tmp = z;
    }

    return tmp;
}

void merge(int* l, int* ll, int lo, int mid1, int mid2, int hi) {
    if (mid2 < hi && l[mid1] <= l[mid1 + 1] && l[mid2] <= l[mid2 + 1])
        return;
    int i, j, k, x;
    for (x = lo; x <= hi; x++)
        ll[x] = l[x];

    i = lo;
    j = mid1 + 1;
    k = mid2 + 1;
    for (x = lo; x <= hi; x++){
        int ret = min(ll, i, j, k, lo, mid1, mid2, hi);

        if (lo <= ret && ret <= mid1)
            l[x] = ll[i++];
        else if (mid1 < ret && ret <= mid2)
            l[x] = ll[j++];
        else if (mid2 < ret && ret <= hi)
            l[x] = ll[k++];
    }
}

void mergeSort(int* l, int* ll, int lo, int hi) {
    if (lo >= hi)
        return;
    if (hi - lo == 1) {
        merge(l, ll, lo, lo, lo + 1, lo + 1);
    }
    else {
        int mid1, mid2, step = (hi - lo + 1) / 3;
        mid1 = lo + step - 1;
        mid2 = lo + step * 2 - 1;
        mergeSort(l, ll, lo, mid1);
        mergeSort(l, ll, mid1 + 1, mid2);
        mergeSort(l, ll, mid2 + 1, hi);
        merge(l, ll, lo, mid1, mid2, hi);
    }
}
