#include <algorithm>
#include <iostream>
#include "selectionSort.h"

void selectionSort1(int* l, int* ll, size_t len, int step) {
    int * i, * j, * min;
    for (i = l; i < l + len - step; i += step) {
        min = i;
        for (j = i + step; j < l + len; j += step)
            if (*j < *min)
                min = j;
        if (min != i) {
            std::copy(i, i + step, ll);
            std::copy(min, min + step, i);
            std::copy(ll, ll + step, min);
        }
    }
}

void merge1(int* l, int* ll, int lo, int mid, int hi) {
    if (l[mid] <= l[mid + 1])
        return;
    int i, j, k;
    for (k = lo; k <= hi; k++)
        ll[k - lo] = l[k];

    i = 0; // lo - lo
    j = mid + 1 - lo;
    for (k = lo; k <= hi; k++){
        if (i > mid - lo)
            l[k] = ll[j++];
        else if (j > hi - lo)
            l[k] = ll[i++];
        else if (ll[j] < ll[i])
            l[k] = ll[j++];
        else
            l[k] = ll[i++];
    }
}

void sort(int* l, int* ll, size_t len, int step) {
    int k, * i, * j;
    for (i = l; i < l + len; i += step)
        selectionSort(i, step);
    std::cout << "line 39: " << std::endl;
    for (i = l; i < l + len; i += step) {
        for (j = i; j < i + step; j++)
            std::cout << *j << " ";
        std::cout << std::endl;
    }
    selectionSort1(l, ll, len, step);
    std::cout << "line 46: " << std::endl;
    for (i = l; i < l + len; i += step) {
        for (j = i; j < i + step; j++)
            std::cout << *j << " ";
        std::cout << std::endl;
    }
    int try_count = 1;
    std::cout << "begin merge: " << std::endl;
    while (1) {
        std::cout << "try " << try_count << " time" << std::endl;
        for (k = 0; k < len - step; k += step) {
            merge1(l, ll, k, k + step - 1, k + step * 2 - 1);
            std::cout << k << " " << k + step - 1 << " " << k + step * 2 -1 << std::endl;
            for (i = l; i < l + len; i += step) {
                for (j = i; j < i + step; j++)
                    std::cout << *j << " ";
                std::cout << std::endl;
            }
            std::cout << "** **" << std::endl;
        }
        bool flag = 1;
        for (k = step; k < len; k += step) {
            if (l[k - 1] > l[k]) {
                flag = 0;
                break;
            }
        }
        if (flag)
            break;
        try_count += 1;
    }
}

int max(int x, int y) {
    if (x > y)
        return x;
    else
        return y;
}

int main() {
    // 思路还是有问题
    int i, m = 50;
    size_t llen, len = 1500;
    int a[len];
    for (i = 0; i < len; i++)
        a[i] = i;
    std::random_shuffle(&a[0], &a[len]);
    for (i = 0; i < len; i++)
        std::cout << a[i] << " ";
    std::cout << std::endl;

    llen = max(m * 2, len / m);
    int aux[llen];
    sort(a, aux, len, m);
    for (i = 0; i < len; i++)
        if (a[i] != i)
            std::cout << a[i] << std::endl;

    return 0;
}
