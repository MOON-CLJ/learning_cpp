#include <array>

template<typename T>
class arrayCircularQueue {
public:
    arrayCircularQueue(): begin(0), end(0), used(0) {}
    bool isEmpty() {
        return (used == 0);
    }
    bool isFull() {
        return (used == size);
    }
    void enqueue(T item) {
        a[end] = item;
        ++end;
        ++used;
        if (end == size)
            end = 0;
    }
    T dequeue() {
        --used;
        if (begin < size - 1)
            return a[begin++];
        else {
            begin = 0;
            return a[size - 1];
        }
    }

private:
    static const int size = 3;
    int begin, end, used;
    std::array<T, size> a;
};
