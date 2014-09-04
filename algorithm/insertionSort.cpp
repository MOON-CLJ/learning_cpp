#include <cstddef>
#include "insertionSort.h"

void insertionSort(int* l, size_t len) {
    int i, j, min, tmp;
    for (int i = 1; i < len; i++) {
        min = i;
        for (int j = i - 1; j >= 0 && l[j] > l[i]; j--)
            min = j;
        tmp = l[i];
        for (int j = i; j > min; j--)
            l[j] = l[j - 1];
        l[min] = tmp;
    }
}
