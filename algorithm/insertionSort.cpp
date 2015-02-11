#include <cstddef>
#include "insertionSort.h"

void insertionSort(int* l, size_t len) {
    size_t i, j, one_next;
    int tmp;
    for (i = 1; i < len; ++i) {
        one_next = i;
        j = i - 1;
        while (l[j] > l[i]) {
            one_next = j;
            if (one_next == 0)
                break;
            --one_next;
        }
        if (one_next != i) {
            tmp = l[i];
            for (j = i; j > one_next; j--)
                l[j] = l[j - 1];
            l[one_next] = tmp;
        }
    }
}
