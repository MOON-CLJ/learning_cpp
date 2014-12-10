#include <iostream>

int prepare_fib_k(int* f, int len) {
    int tmp = 1;
    while (f[tmp] < len - 1) {
        ++tmp;
        f[tmp] = f[tmp - 1] + f[tmp - 2];
    }
    return tmp;
}

int binary_search_fib(const int* l, const int* f, int len, int k, int value) {
    int low = 0;
    int mid;
    while (low < len) {
        if (k < 2) {
            std::cout << k << std::endl;
            if (l[low] == value)
                return low;
            else if (l[low + 1] == value)
                return low + 1;
        } else {
            mid = low + f[k] - f[k - 1];
            std::cout << low << " " << f[k] << " " << low << "+" << f[k] - f[k - 1] << " " << k << std::endl;
            if (mid > len - 1) {
                --k;
                continue;
            }
            if (l[mid] == value)
                return mid;
            else if (l[mid] > value)
                k -= 2;
            else {
                --k;
                low = mid;
            }
        }
    }
    return -1;
}

int main() {
    const int len = 15;
    int i;
    int a[1000], f[1000];
    for (i = 0; i < len; i++) {
        a[i] = i;
        f[i] = 0;
    }
    f[0] = 1;
    f[1] = 1;
    int k = prepare_fib_k(f, len);
    std::cout << k << std::endl;
    for (int i = 0; i < len; i++)
        std::cout << f[i] << " ";
    std::cout << std::endl;
    int found = binary_search_fib(a, f, len, k, len - 1);
    if (found != -1)
        std::cout << found << std::endl;

    return 0;
}
