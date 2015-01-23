#include <iostream>

template<typename T>
class MinPQ {
public:
    MinPQ(size_t MaxN): N(0) {
        pq = new T[MaxN + 1];
    }
    bool isEmpty() {
        return N == 0;
    }
    size_t size() { return N; }
    void insert(T v) {
        pq[++N] = v;
        swin(N);
    }
    T delMin() {
        T min = pq[1];
        exch(1, N--);
        sink(1);
        return min;
    }

private:
    T* pq;
    size_t N;

    bool more(size_t i, size_t j) {
        return pq[i] > pq[j];
    }
    void exch(size_t i, size_t j) {
        T tmp = pq[i];
        pq[i] = pq[j];
        pq[j] = tmp;
    }
    void swin(size_t k) {
        while (k > 1 && more(k/2, k)) {
            exch(k, k/2);
            k = k/2;
        }
    }
    void sink(size_t k) {
        while (2*k <= N) {
            size_t j = 2*k;
            if (j < N && more(j, j+1)) j++;
            if (!more(k, j)) break;
            exch(k, j);
            k = j;
        }
    }
};
