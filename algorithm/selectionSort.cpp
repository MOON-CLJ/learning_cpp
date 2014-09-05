#include <iostream>
#include "selectionSort.h"

void selectionSort(int* l, size_t len) {
    int i, j, min, tmp;
    for (i = 0; i < len - 1; i++) {
        min = i;
        for (j = i + 1; j < len; j++)
            if (l[j] < l[min])
                min = j;
        if (min != i) {
            tmp = l[i];
            l[i] = l[min];
            l[min] = tmp;
        }
    }
}
