#include <iostream>

void sort(int* l, size_t len) {
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

int main() {
    int a[] = {6, 3, 1, 5, 2, 8, 7, 10, 11};
    int i;
    size_t len = sizeof(a) / sizeof(*a);
    sort(a, len);
    for (i = 0; i < len; i++)
        std::cout << a[i] << std::endl;
    return 0;
}
