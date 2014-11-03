#include <iostream>

#include "doublyLinkedList.h"

void printList(doublyLinkedList<char>& s) {
    Node<char>* curr = s.getFirst();
    while (curr) {
        std::cout << curr->val << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}

int main() {
    doublyLinkedList<char> mybuffer;
    mybuffer.insertLast('w');
    mybuffer.insertLast('o');
    mybuffer.insertLast('s');
    mybuffer.insertLast('h');
    mybuffer.insertLast('i');
    mybuffer.insertLast('c');
    mybuffer.insertLast('l');
    mybuffer.insertLast('j');
    printList(mybuffer);

    Node<char>* curr = mybuffer.getFirst();
    Node<char>* newNode;
    while (curr->val != 'o')
        curr = curr->next;
    newNode = new Node<char>;
    newNode->val = 'b';
    mybuffer.insertAfter(curr, newNode);
    curr = curr->next;
    newNode = new Node<char>;
    newNode->val = 'u';
    mybuffer.insertAfter(curr, newNode);
    printList(mybuffer);

    curr = curr->pre;
    mybuffer.removeAfter(curr);
    mybuffer.removeAfter(curr);
    printList(mybuffer);

    return 0;
}
