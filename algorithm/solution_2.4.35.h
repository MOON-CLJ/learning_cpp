#include <iostream>
#include <stdlib.h>

template<typename T>
class Sample {
public:
    Sample(size_t N, T* init) {
        size_t i;
        pq = new T[N + 1];
        weight = new T[N + 1];
        for (i = 0; i < N; i++) {
            pq[i + 1] = init[i];
            weight[i + 1] = init[i];
        }
        for (i = N / 2; i > 0; i--)
            weight[i] += (weight[i * 2] + weight[i * 2 + 1]);
    }
    T random() {
        T rand_weight = rand() % weight[1];
        size_t i = 1;
        while (rand_weight >= pq[i]) {
            rand_weight -= pq[i];
            i *= 2;
            if (rand_weight >= weight[i]) {
                rand_weight -= weight[i];
                i += 1;
            }
        }
        return i - 1;
    }
    void change(size_t i, T v) {
        ++i;
        if (v == pq[i])
            return;
        T diff = v - pq[i];
        pq[i] = v;
        while (i > 0) {
            weight[i] += diff;
            i /= 2;
        }
    }

private:
    T* pq;
    T* weight;
};
