#include <iostream>

#include "stack.h"

void printStack(stack<int>& s) {
    Node<int>* curr = s.getFirst();
    while (curr) {
        std::cout << curr->val << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}

int main() {
    stack<int> mystack;
    int i;
    for (i = 0; i < 10; i++)
        mystack.push(i);
    printStack(mystack);
    Node<int>* curr = mystack.getFirst();
    while (curr->val != 8)
        curr = curr->next;
    mystack.removeAfter(curr);
    printStack(mystack);

    while (curr->val != 0)
        curr = curr->next;
    mystack.removeAfter(curr);
    printStack(mystack);

    mystack.removeAfter(NULL);
    printStack(mystack);

    Node<int>* newNode = new Node<int>;
    newNode->val = 7;
    newNode->next = NULL;
    curr = mystack.getFirst();
    while (curr->val != 8)
        curr = curr->next;
    mystack.insertAfter(curr, newNode);
    printStack(mystack);

    mystack.insertAfter(curr, NULL);
    printStack(mystack);

    mystack.insertAfter(NULL, NULL);
    printStack(mystack);

    return 0;
}
