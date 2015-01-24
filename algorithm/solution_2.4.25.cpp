#include <iostream>
#include <cmath>

#include "MinPQ.h"

struct X {
    long val;
    int i;
    int j;

    X() {}
    X(int i, int j): i(i), j(j) {
        val = (long) std::pow(i, 3) + (long) std::pow(j, 3);
    }
    inline bool operator>(const X& other) {
        return other.val < val;
    }
};

int main() {
    int i;
    const int N = 1000000;
    MinPQ<X> pq(N);
    for (i = 0; i <= N; i++)
        pq.insert(X(i, 0));

    long last_val = 0;
    int last_i = 0;
    int last_j = 0;

    while (!pq.isEmpty()) {
        X tmp = pq.delMin();
        if (tmp.val != last_val) {
            last_val = tmp.val;
            last_i = tmp.i;
            last_j = tmp.j;
        } else {
            if (!(last_i == tmp.j && last_j == tmp.i)) {
                std::cout << "<<-- -->>" << std::endl;
                std::cout << last_val << " " << last_i << " " << last_j << std::endl;
                std::cout << tmp.val << " " << tmp.i << " " << tmp.j << std::endl;
            }
            last_i = tmp.i;
            last_j = tmp.j;
        }
        if (tmp.j < N)
            pq.insert(X(tmp.i, tmp.j + 1));
    }
    return 0;
}
