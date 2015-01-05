#include "MaxPQ.h"

int main() {
    size_t i;
    char a[] = {'P', 'R', 'I', 'O', '*', 'R', '*', '*', 'I', '*', 'T', '*', 'Y', '*',
        '*', '*', 'Q', 'U', 'E', '*', '*', '*', 'U', '*', 'E'};

    MaxPQ<char> pq(10);
    for (i = 0; i < (sizeof(a) / sizeof(*a)); i++) {
        if (a[i] == '*')
            std::cout << pq.delMax() << std::endl;
        else
            pq.insert(a[i]);
    }

    return 0;
}
