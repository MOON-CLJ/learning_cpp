#include <iostream>

#include "solution_1.3.30.h"

void print(Node<int>* const first) {
    Node<int>* curr = first;
    while(curr) {
        std::cout << curr->val << " ";
        curr = curr->next ;
    }
    std::cout << std::endl;
}

int main() {
    Node<int> * head = NULL;
    int i;
    for(i=1; i<=10; i++) {
        Node<int> * curr = new Node<int>;
        curr->val = i;
        curr->next = head;
        head = curr;
    }
    print(head);
    reverseLinkedList(head);
    print(head);
    return 0;
}
