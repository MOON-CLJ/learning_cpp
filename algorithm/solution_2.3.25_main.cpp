#include <iostream>
#include <time.h>
#include <sys/time.h>  // gettimeofday
#include "quickSort1.h"

int main() {
    // solution_2.3.25.cpp
    int N = 1000, M;
    while (N <= 1000000) {
        std::cout << "N(" << N << "): ";
        for (M = 0; M <= 30; M++) {
            int i, j;
            size_t len = N;
            size_t extra_len = N;
            int a[len + extra_len];
            for (i = 0; i < len; i++)
                a[i] = i;
            srand(time(NULL));
            for (i = len; i < len + extra_len; i++) {
                j = rand() % len;
                a[i] = a[j];
            }
            len += extra_len;
            std::random_shuffle(&a[0], &a[len]);
            struct timeval tv_begin, tv_end;
            gettimeofday(&tv_begin, NULL);
            quickSort(a, len, M);
            gettimeofday(&tv_end, NULL);
            std::cout << (tv_end.tv_sec - tv_begin.tv_sec) * 1000000 + (tv_end.tv_usec - tv_begin.tv_usec) << " ";

            for (i = 0; i < len - 1; i++)
                if (a[i] > a[i + 1])
                    std::cout << a[i] << std::endl;
        }
        std::cout << std::endl;
        N *= 10;
    }
    return 0;
}
