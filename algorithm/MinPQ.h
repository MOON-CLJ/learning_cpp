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
        int first_val = pq[k];
        int last_idx = k;
        while (k > 1 && more(k/2, k)) {
            pq[last_idx] = pq[k/2];
            last_idx = k/2;
            k = k/2;
        }
        pq[last_idx] = first_val;
    }
    void sink(size_t k) {
        int first_val = pq[k];
        int last_idx = k;
        while (2*k <= N) {
            size_t j = 2*k;
            if (j < N && more(j, j+1)) ++j;
            if (!(first_val > pq[j])) break;
            pq[last_idx] = pq[j];
            last_idx = j;
            k = j;
        }
        pq[last_idx] = first_val;
    }
};
