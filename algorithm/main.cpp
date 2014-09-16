#include <iostream>
#include <algorithm>
//#include "mergeSortBU.h"
//#include "selectionSort.h"
//#include "solution_2.2.16.h"
//#include "solution_2.2.19.h"
//#include "solution_2.2.20.h"
//#include "solution_2.2.22.h"
#include "quickSort.h"
//#include "solution_2.3.5.h"
//#include "solution_2.3.15.h"


/*
int main() {
    // mergeSortBU.cpp
    int i;
    size_t len = 200201;
    int a[len];
    for (i = 0; i < len; i++)
        a[i] = i;
    std::random_shuffle(&a[0], &a[len]);
    int aux[len];
    int * l = (int *) a;
    int * ll = (int *) aux;
    mergeSort(l, ll, len);
    for (i = 0; i < len; i++)
        if (a[i] != i)
            std::cout << a[i] << std::endl;

    return 0;
}

int main() {
    // selectionSort.cpp
    int a[] = {6, 3, 1, 5, 2, 8, 7, 10, 11};
    int i;
    size_t len = sizeof(a) / sizeof(*a);
    selectionSort(a, len);
    for (i = 0; i < len; i++)
        std::cout << a[i] << std::endl;
    return 0;
}

int main() {
    // solution_2.2.16.cpp
    int i;
    size_t len = 16161;
    int a[len];
    for (i = 0; i < len; i++)
        a[i] = i;
    std::random_shuffle(&a[0], &a[len]);
    int aux[len];
    mergeSortBU1(a, aux, len);
    for (i = 0; i < len; i++)
        if (a[i] != i)
            std::cout << a[i] << std::endl;

    return 0;
}

int main() {
    // solution_2.2.19.cpp
    int i, cnt = 0;
    size_t len = 6;
    int a[6] = {6, 5, 4, 3, 2, 1};
    int aux[len];
    mergeSort(a, aux, 0, len - 1, cnt);
    for (i = 0; i < len; i++)
        if (a[i] != i)
            std::cout << a[i] << std::endl;

    std::cout << cnt << std::endl;
    return 0;
}

int main() {
    // solution_2.2.20.cpp
    int i;
    size_t len = 20206;
    int a[len];
    for (i = 0; i < len; i++)
        a[i] = i;
    std::random_shuffle(&a[0], &a[len]);

    int p[len];
    for (i = 0; i < len; i++)
        p[i] = i;

    int pux[len];
    mergeSortBU(a, p, pux, len);
    for (i = 0; i < len; i++)
        if (a[p[i]] != i)
            std::cout << a[p[i]] << std::endl;

    return 0;
}

int main() {
    // solution_2.2.22.cpp
    int i;
    size_t len = 10013;
    int a[len];
    for (i = 0; i < len; i++)
        a[i] = i;
    std::random_shuffle(&a[0], &a[len]);
    int aux[len];
    mergeSort(a, aux, 0, len - 1);
    for (i = 0; i < len; i++)
        if (a[i] != i)
            std::cout << a[i] << std::endl;

    return 0;
}
*/

int main() {
    // quickSort.cpp
    int i;
    size_t len = 10013;
    int a[len];
    for (i = 0; i < len; i++)
        a[i] = i;
    std::random_shuffle(&a[0], &a[len]);
    quickSort(a, len);
    for (i = 0; i < len; i++)
        if (a[i] != i)
            std::cout << a[i] << std::endl;
    return 0;
}

/*
int main() {
    // solution_2.3.5.cpp
    int i;
    size_t len = 6;
    int a[6] = {1, 1, 0, 0, 1, 0};
    sort(a, len);
    for (i = 0; i < len; i++)
        if (a[i] != i)
            std::cout << a[i] << std::endl;
    return 0;
}

int main() {
    // solution_2.3.15.cpp
    int i;
    size_t len = 93936;
    int a[len], aa[len];
    for (i = 0; i < len; i++) {
        a[i] = i;
        aa[i] = i;
    }
    std::random_shuffle(&a[0], &a[len]);
    std::random_shuffle(&aa[0], &aa[len]);
    NutsBoltsSort(a, aa, len);
    for (i = 0; i < len; i++) {
        if (a[i] != i)
            std::cout << "a: " << a[i] << std::endl;
        if (aa[i] != i)
            std::cout << "aa: " << aa[i] << std::endl;
    }
    return 0;
}
*/
