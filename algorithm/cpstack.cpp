#include <iostream>

#include "stack.h"

void cpStack(stack<int>& from, stack<int>& to) {
    Node<int>* fromCurr = from.getFirst();
    Node<int>* toFirst = NULL;
    Node<int>* toTail = NULL;
    while (fromCurr) {
        Node<int>* newNode = new Node<int>;
        newNode->val = fromCurr->val;
        newNode->next = NULL;
        if (toFirst == NULL) {
            toFirst = newNode;
            toTail = toFirst;
        }
        else {
            toTail->next = newNode;
            toTail = toTail->next;
        }
        fromCurr = fromCurr->next;
    }
    to.setFirst(toFirst);
}

void cpStack1(stack<int>& from, stack<int>& to) {
    Node<int>* fromCurr = from.getFirst();
    Node<int>* toFirst = NULL;
    Node<int>** toTail = &toFirst;
    while (fromCurr) {
        *toTail = new Node<int>;
        (*toTail)->val = fromCurr->val;
        (*toTail)->next = NULL;
        toTail = &((*toTail)->next);
        fromCurr = fromCurr->next;
    }
    to.setFirst(toFirst);
}

void printStack(stack<int>& s) {
    Node<int>* curr = s.getFirst();
    while (curr) {
        std::cout << curr->val << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}

int main() {
    int i;
    stack<int> stack1;
    for (i = 0; i < 10; i++)
        stack1.push(i);

    printStack(stack1);
    stack<int> stack2;
    cpStack(stack1, stack2);
    printStack(stack2);
    stack<int> stack3;
    cpStack1(stack1, stack3);
    printStack(stack3);

    return 0;
}
