#include <iostream>

template<typename T>
struct Node {
    T val;
    Node<T> * next;
};

template<typename T>
class stack {
public:
    stack(): first(NULL), N(0) {}
    bool isEmpty() {
        return (first == NULL);
    }
    int size() {return N;}
    void push(T item) {
        Node<T>* newNode = new Node<T>;
        newNode->val = item;
        newNode->next = first;
        first = newNode;
        N++;
    }
    T pop() {
        Node<T>* oldFirst = first;
        T item = first->val;
        first = first->next;
        delete oldFirst;
        N--;
        return item;
    }
    T peek() {
        return first->val;
    }
    Node<T>* getFirst() {
        return first;
    }
    void setFirst(Node<T>* newFirst) {
        first = newFirst;
    }

private:
    Node<T> * first;
    int N;
};
