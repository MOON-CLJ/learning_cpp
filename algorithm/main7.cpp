#include <iostream>

#include "arrayCircularQueue.h"

int main() {
    arrayCircularQueue<int> myqueue;
    myqueue.enqueue(1);
    std::cout << myqueue.isEmpty() << " " << myqueue.isFull() << std::endl;
    myqueue.enqueue(2);
    std::cout << myqueue.isEmpty() << " " << myqueue.isFull() << std::endl;
    myqueue.enqueue(3);
    std::cout << myqueue.isEmpty() << " " << myqueue.isFull() << std::endl;
    std::cout << myqueue.dequeue() << std::endl;
    std::cout << myqueue.isEmpty() << myqueue.isFull() << std::endl;
    std::cout << myqueue.dequeue() << std::endl;
    std::cout << myqueue.isEmpty() << myqueue.isFull() << std::endl;
    std::cout << myqueue.dequeue() << std::endl;
    std::cout << myqueue.isEmpty() << myqueue.isFull() << std::endl;
    return 0;
}
