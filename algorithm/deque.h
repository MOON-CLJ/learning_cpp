#include <iostream>

template<typename T>
struct Node {
    T val;
    Node<T> * next;
    Node<T> * pre;
};

template<typename T>
class deque{
public:
    deque(): first(NULL), last(NULL), N(0) {}
    bool isEmpty() {
        return (first == NULL);
    }
    int size() {return N;}
    void pushRight(T item) {
        Node<T>* newNode = new Node<T>;
        newNode->val = item;
        newNode->next = NULL;
        if (isEmpty()) {
            newNode->pre = NULL;
            first = newNode;
            last = newNode;
        }
        else {
            newNode->pre = last;
            last->next = newNode;
            last = last->next;
        }
        ++N;
    }
    void pushLeft(T item) {
        Node<T>* newNode = new Node<T>;
        newNode->val = item;
        newNode->pre = NULL;
        if (isEmpty()) {
            newNode->next = NULL;
            first = newNode;
            last = newNode;
        }
        else {
            newNode->next = first;
            first->pre = newNode;
            first = newNode;
        }
        ++N;
    }
    T popLeft() {
        Node<T>* oldFirst = first;
        T item = first->val;
        if (first != last) {
            first = first->next;
            first->pre = NULL;
        }
        else {
            first = NULL;
            last = NULL;
        }
        delete oldFirst;
        --N;
        return item;
    }
    T popRight() {
        Node<T>* oldLast = last;
        T item = last->val;
        if (first != last) {
            last = last->pre;
            last->next = NULL;
        }
        else {
            first = NULL;
            last = NULL;
        }
        delete oldLast;
        --N;
        return item;
    }

private:
    Node<T> * first;
    Node<T> * last;
    int N;
};
