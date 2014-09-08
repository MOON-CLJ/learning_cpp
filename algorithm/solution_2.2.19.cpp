#include <iostream>
#include "solution_2.2.19.h"

void merge(int* l, int* ll, int lo, int mid, int hi, int& cnt) {
    if (l[mid] <= l[mid + 1])
        return;
    int i, j, k;
    for (k = lo; k <= hi; k++)
        ll[k] = l[k];

    i = lo;
    j = mid + 1;
    for (k = lo; k <= hi; k++){
        if (i > mid)
            l[k] = ll[j++];
        else if (j > hi)
            l[k] = ll[i++];
        else if (ll[j] < ll[i]) {
            cnt += (mid - i + 1);
            std::cout << "add " << mid - i + 1 << std::endl;
            l[k] = ll[j++];
        }
        else
            l[k] = ll[i++];
    }
}

void mergeSort(int* l, int* ll, int lo, int hi, int& cnt) {
    if (lo >= hi)
        return;
    int mid = (lo + hi) / 2;
    mergeSort(l, ll, lo, mid, cnt);
    mergeSort(l, ll, mid + 1, hi, cnt);
    merge(l, ll, lo, mid, hi, cnt);
}
