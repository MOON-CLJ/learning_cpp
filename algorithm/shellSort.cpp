#include <iostream>
#include <stdlib.h>
#include <time.h>

/*
void sort(int* l, size_t len) {
    int i, j, tmp, h = 1;
    while (h < len / 3)
        h = 3 * h + 1;
    while (h >= 1) {
        for (i = h; i < len; i++) {
            for (j = i; j >= h && l[j] < l[j - h]; j -= h) {
                tmp = l[j - h];
                l[j - h] = l[j];
                l[j] = tmp;
            }
        }
        h /= 3;
    }
}
*/

void sort(int* l, size_t len) {
    int i, j, tmp, min, h = 1;
    while (h < len / 3)
        h = 3 * h + 1;
    while (h >= 1) {
        for (i = h; i < len; i++) {
            min = i;
            for (j = i; j >= h && l[j - h] > l[i]; j -= h)
                min = j - h;
            if (min != i) {
                tmp = l[i];
                for (j = i; j > min; j -= h)
                    l[j] = l[j - h];
                l[min] = tmp;
            }
        }
        h /= 3;
    }
}

int main() {
    int a[] = {6, 3, 1, 5, 2, 8, 7, 10, 11};
    int i;
    size_t len = sizeof(a) / sizeof(*a);
    sort(a, len);
    for (i = 0; i < len; i++)
        std::cout << a[i] << std::endl;
    return 0;
}

/*
void sort(int* l, size_t len) {
    int i, j, tmp, count, h = 1;
    while (h < len / 3)
        h = 3 * h + 1;
    while (h >= 1) {
        count = 0;
        for (i = h; i < len; i++) {
            for (j = i; j >= h && l[j] < l[j - h]; j -= h) {
                count += 1;
                tmp = l[j - h];
                l[j - h] = l[j];
                l[j] = tmp;
            }
            if (j >= h)
                count += 1;
        }
        std::cout << count * 1.0 / len << std::endl;
        h /= 3;
    }
}

int a[10000000] = {};

int main() {
    int initlen = 100, maxlen = 10000000;
    int i;
    srand (time(NULL));
    while (initlen <= maxlen) {
        std::cout << "len: " << initlen << std::endl;
        for (i = 0; i < initlen; i++) {
            a[i] = rand() % 100000;
        }
        sort(a, initlen);
        initlen *= 10;
    }
    return 0;
}
*/
