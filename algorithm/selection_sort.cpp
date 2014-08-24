#include <iostream>

void sort(int* l) {
    int i, j, len, min, tmp;
    len = sizeof(l);
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
    int a[] = {6, 3, 1, 5, 2, 8, 7, 10};
    int i;
    sort(a);
    for (i = 0; i < sizeof(a) / sizeof(*a); i++)
        std::cout << a[i] << std::endl;
    return 0;
}
