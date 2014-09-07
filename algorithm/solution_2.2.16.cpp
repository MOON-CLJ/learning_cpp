#include <iostream>
#include "solution_2.2.16.h"

void mergeSortBU1(int* l, int* ll, size_t len) {
    int lo, mid, hi;
    bool flag;
    while (1) {
        flag = false;
        lo = 0;
        while (lo < len) {
            for (mid = lo; mid < len - 1 && l[mid] < l[mid + 1]; mid++);
            for (hi = mid + 1; hi < len - 1 && l[hi] < l[hi + 1]; hi++);

            if (hi < len && lo < hi) {
                merge(l, ll, lo, mid, hi);
                flag = true;
            }
            lo = hi + 1;
        }
        if (!flag)
            break;
    }
}
