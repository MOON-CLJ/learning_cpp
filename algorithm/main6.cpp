#include <iostream>

#include "doublyLinkedList.h"

void printStack(doublyLinkedList<int>& l) {
    Node<int>* curr = l.getFirst();
    while (curr) {
        std::cout << curr->val << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}


int main() {
    doublyLinkedList<int> l;
    for (int i = 0; i < 10; i++)
        l.push(i);
    printStack(l);

    l.push(7);
    l.push(8);
    l.push(9);
    printStack(l);
    l.pop();
    printStack(l);
    l.pop();
    printStack(l);
    l.pop();
    printStack(l);

    l.insertLast(2);
    l.insertLast(1);
    l.insertLast(0);
    printStack(l);
    l.removeLast();
    printStack(l);
    l.removeLast();
    printStack(l);
    l.removeLast();
    printStack(l);

    return 0;
}
