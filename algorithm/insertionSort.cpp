#include <cstddef>
#include "insertionSort.h"

void insertionSort(int* l, size_t len) {
    int i, j, min, tmp;
    for (i = 1; i < len; i++) {
        min = i;
        for (j = i - 1; j >= 0 && l[j] > l[i]; j--)
            min = j;
        tmp = l[i];
        for (j = i; j > min; j--)
            l[j] = l[j - 1];
        l[min] = tmp;
    }
}
