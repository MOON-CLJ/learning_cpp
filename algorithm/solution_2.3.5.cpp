#include "solution_2.3.5.h"

void exch(int* l, int i, int j) {
    int tmp = l[i];
    l[i] = l[j];
    l[j] = tmp;
}

void sort(int* l, size_t len) {
    int i, j, min, max;
    min = l[0];
    max = min;
    for (i = 1; i < len; i++) {
        if (min != l[i]) {
            if (min > l[i]) {
                min = l[i];
            }
            else if (max < l[i]) {
                max = l[i];
            }
            break;
        }
    }
    i = -1;
    j = len;
    while (1) {
        while (l[++i] == min) {
            if (i == len - 1)
                break;
        }
        while (l[--j] == max) {
            if (j == 0)
                break;
        }
        if (i >= j)
            break;
        exch(l, i, j);
    }
}
