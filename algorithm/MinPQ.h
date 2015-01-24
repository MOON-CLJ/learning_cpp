#include <iostream>

template<typename T>
class MinPQ {
public:
    MinPQ(size_t MaxN): N(0), MaxN(MaxN) {
        pq = new T[MaxN + 1];
    }
    bool isEmpty() {
        return N == 0;
    }
    size_t size() { return N; }
    void insert(T v) {
        if (N == MaxN)
            resize(2 * MaxN);
        pq[++N] = v;
        swin(N);
    }
    T delMin() {
        T min = pq[1];
        exch(1, N--);
        sink(1);
        if (N > 0 && N == MaxN / 4)
            resize(MaxN / 2);
        return min;
    }

private:
    T* pq;
    size_t N;
    size_t MaxN;

    void resize(size_t NewMaxN) {
        T* new_pq = new T[NewMaxN + 1];

        memcpy(new_pq, pq, (N + 1) * sizeof(T));
        MaxN = NewMaxN;
        delete[] pq;
        pq = new_pq;
    }

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
