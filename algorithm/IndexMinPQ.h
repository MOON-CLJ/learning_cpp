#include <iostream>
#include <stdexcept>

template<typename T>
class IndexMinPQ {
public:
    IndexMinPQ(int MaxN): N(0) {
        pq = new int[MaxN + 1];
        qp = new int[MaxN + 1];
        keys = new T[MaxN + 1];
        for (int i = 0; i <= MaxN; i++) qp[i] = -1;
    }
    bool isEmpty() {
        return N == 0;
    }
    bool contains(int k) {
        return qp[k] != -1;
    }
    int size() { return N; }
    void insert(int k, T v) {
        if (contains(k))
            throw std::invalid_argument("index is already in the priority queue");
        pq[++N] = k;
        qp[k] = N;
        keys[k] = v;
        swin(N);
    }
    void changeKey(int k, T v) {
        if (!contains(k))
            throw std::invalid_argument("index is not in the priority queue");
        keys[k] = v;
        swin(k);
        sink(k);
    }
    int delMin() {
        if (isEmpty())
            throw std::underflow_error("Priority queue underflow");
        int indexOfMin = pq[1];
        exch(1, N--);
        sink(1);
        qp[pq[N + 1]] = -1;
        return indexOfMin;
    }
    void deleteKey(int k) {
        if (!contains(k))
            throw std::invalid_argument("index is not in the priority queue");
        int index = qp[k];
        exch(index, N--);
        swin(index);
        sink(index);
        qp[k] = -1;
    }
    T minKey() {
        if (isEmpty())
            throw std::underflow_error("Priority queue underflow");
        return keys[pq[1]];
    }
    int minIndex() {
        if (isEmpty())
            throw std::underflow_error("Priority queue underflow");
        return pq[1];
    }

private:
    int* pq;
    int* qp;
    T* keys;
    int N;

    bool more(int i, int j) {
        return keys[pq[i]] > keys[pq[j]];
    }
    void exch(int i, int j) {
        int tmp = pq[i];
        pq[i] = pq[j];
        pq[j] = tmp;
        qp[pq[i]] = i;
        qp[pq[j]] = j;
    }
    void swin(int k) {
        while (k > 1 && more(k/2, k)) {
            exch(k, k/2);
            k = k/2;
        }
    }
    void sink(int k) {
        while (2*k <= N) {
            int j = 2*k;
            if (j < N && more(j, j+1)) j++;
            if (!more(k, j)) break;
            exch(k, j);
            k = j;
        }
    }
};
