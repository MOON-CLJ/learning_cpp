#include <iostream>

#include "MinPQ.h"
#include "MaxPQ.h"


template<typename T>
class MedianPQ {
public:
    MedianPQ(size_t MaxN): N(0), min_pq(MaxN), max_pq(MaxN) {}
    bool isEmpty() {
        return N == 0;
    }
    size_t size() { return N; }
    void insert(T v) {
        if (!min_pq.isEmpty() && min_pq.min() < v)
            min_pq.insert(v);
        else
            max_pq.insert(v);
        if (max_pq.size() < min_pq.size()) {
            T min = min_pq.delMin();
            max_pq.insert(min);
        } else if (max_pq.size() > min_pq.size()+1) {
            T max = max_pq.delMax();
            min_pq.insert(max);
        }
        ++N;
    }
    T delMedian() {
        T median = max_pq.delMax();
        if (max_pq.size() < min_pq.size()) {
            T min = min_pq.delMin();
            max_pq.insert(min);
        }
        --N;
        return median;
    }
    T Median() {
        return max_pq.max();
    }
    void print() {
        std::cout << "min" << std::endl;
        min_pq.print();
        std::cout << "max" << std::endl;
        max_pq.print();
        std::cout << std::endl;
    }

private:
    size_t N;
    MinPQ<T> min_pq;
    MaxPQ<T> max_pq;
};
