#include <iostream>

template<typename T>
struct Node {
    T val;
    Node<T> * next;
};

template<typename T>
class steque {
public:
    steque(): first(NULL), last(NULL), N(0) {}
    bool isEmpty() {
        return (first == NULL);
    }
    int size() {return N;}
    void push(T item) {
        Node<T>* newNode = new Node<T>;
        newNode->val = item;
        newNode->next = first;
        if (isEmpty()) {
            first = newNode;
            last = newNode;
        }
        else
            first = newNode;
        ++N;
    }
    T pop() {
        Node<T>* oldFirst = first;
        T item = first->val;
        first = first->next;
        if (isEmpty())
            last = NULL;
        delete oldFirst;
        --N;
        return item;
    }
    void enqueue(T item) {
        Node<T>* newNode = new Node<T>;
        newNode->val = item;
        newNode->next = NULL;
        if (isEmpty()) {
            first = newNode;
            last = newNode;
        }
        else {
            last->next = newNode;
            last = newNode;
        }
        ++N;
    }

private:
    Node<T> * first;
    int N;
};
