#ifndef SOLUTION1_3_30_H
#define SOLUTION1_3_30_H

#include <iostream>

template<typename T>
struct Node {
    T val;
    Node<T> * next;
};

template<typename T>
void reverseLinkedList(Node<T>*& first) {
    Node<T>* curr = first;
    Node<T>* last = NULL;
    while (1) {
        first = first->next;
        curr->next = last;
        last = curr;
        if (first)
            curr = first;
        else
            break;
    }
    first = curr;
}

#endif
