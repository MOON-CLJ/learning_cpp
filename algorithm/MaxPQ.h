#include <iostream>

template<typename T>
class MaxPQ {
public:
    MaxPQ(int MaxN): N(0) {
        pq = new T[MaxN + 1];
    }
    bool isEmpty() {
        return N == 0;
    }
    int size() { return N; }
    void insert(T v) {
        pq[++N] = v;
        swin(N);
    }
    T delMax() {
        T max = pq[1];
        exch(1, N--);
        sink(1);
        return max;
    }

private:
    T* pq;
    int N;

    bool less(int i, int j) {
        return pq[i] < pq[j];
    }
    void exch(int i, int j) {
        T tmp = pq[i];
        pq[i] = pq[j];
        pq[j] = tmp;
    }
    void swin(int k) {
        while (k > 1 && less(k/2, k)) {
            exch(k, k/2);
            k = k/2;
        }
    }
    void sink(int k) {
        while (2*k <= N) {
            int j = 2*k;
            if (j < N && less(j, j+1)) j++;
            if (!less(k, j)) break;
            exch(k, j);
            k = j;
        }
    }
};
