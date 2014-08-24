#include <iostream>

int main() {
    int a[] = {1, 2, 3};
    int i;
    for (i=0; i< sizeof(a) / sizeof(*a); i++)
        std::cout << a[i] << std::endl;
    return 0;
}
