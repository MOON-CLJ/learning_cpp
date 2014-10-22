#include <iostream>

#include "queue.h"
#include "circularQueue.h"

int main() {
    std::string str[17] = {"to", "be", "or", "not", "to", "-", "be", "-", "-", "that",
        "-", "-", "-", "is"};
    queue<std::string> myqueue;
    for (int i = 0; i < 17; i++) {
        if (str[i].compare("-") == 0)
            std::cout << myqueue.dequeue() << std::endl;
        else
            myqueue.enqueue(str[i]);
    }
    std::cout << "--" << std::endl;
    circularQueue<std::string> myqueue1;
    for (int i = 0; i < 17; i++) {
        if (str[i].compare("-") == 0)
            std::cout << myqueue1.dequeue() << std::endl;
        else
            myqueue1.enqueue(str[i]);
    }

    return 0;
}
