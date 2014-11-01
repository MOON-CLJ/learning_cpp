#include <iostream>

#include "circularQueue.h"

int main() {
    int i;
    circularQueue<int> myqueue;
    for (i = 0; i < 7; i++)
        myqueue.enqueue(i);

    Node<int>* curr = myqueue.getLast();
    while (!myqueue.isEmpty()) {
        for (i = 0; i < 1; i++) {
            curr = curr->next;
            i++;
        }
        std::cout << curr->next->val << std::endl;
        myqueue.removeAfter(curr);
    }
    return 0;
}
