#include <iostream>

int search_max(const int* l, int lo, int hi) {
    int mid;
    if (lo == hi)
        return lo;
    while (lo < hi) {
        mid = (lo + hi) / 2;
        if (hi - lo > 1) {
            if (l[mid - 1] < l[mid] && l[mid] > l[mid + 1])
                return mid;
            else if (l[mid - 1] < l[mid] && l[mid] < l[mid + 1])
                lo = mid;
            else if (l[mid - 1] > l[mid] && l[mid] > l[mid + 1])
                hi = mid;
        } else {
            if (l[lo] < l[hi])
                return hi;
            else
                return lo;
        }
    }
}

int binary_search(const int* l, int lo, int hi, int value, int reverse) {
    int mid;
    while (lo <= hi) {
        mid = (lo + hi) / 2;
        if (l[mid] == value)
            return mid;
        if (reverse == 0) {
            if (l[mid] < value)
                lo = mid + 1;
            else
                hi = mid - 1;
        }
        else {
            if (l[mid] > value)
                lo = mid + 1;
            else
                hi = mid - 1;
        }
    }
    return -1;
}

int main() {
    int a[10] = {0, 2, 5, 6, 7, 9, 10, 8, 3, 1};
    int max_idx = search_max(a, 0, 9);
    std::cout << max_idx << std::endl;
    int f = binary_search(a, 0, max_idx, 1, 0);
    if (f != -1)
        std::cout << f << std::endl;
    f = binary_search(a, max_idx + 1, 9, 1, 1);
    if (f != -1)
        std::cout << f << std::endl;

    return 0;
}
