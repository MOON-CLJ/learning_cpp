#include <iostream>

template<typename T>
class stack {
public:
    stack(): first(NULL), N(0) {}
    bool isEmpty() {
        return (first == NULL);
    }
    int size() {return N;}
    void push(T item) {
        Node* newNode = new Node;
        newNode->val = item;
        newNode->next = first;
        first = newNode;
        N++;
    }
    T pop() {
        Node* oldFirst = first;
        T item = first->val;
        first = first->next;
        delete oldFirst;
        N--;
        return item;
    }

private:
    struct Node {
        T val;
        Node * next;
    };
    Node * first;
    int N;
};
