#include <iostream>

template<typename T>
struct Node {
    T val;
    Node<T> * next;
    Node<T> * pre;
};

template<typename T>
class doublyLinkedList {
public:
    doublyLinkedList(): first(NULL), last(NULL), N(0) {}
    bool isEmpty() {
        return (first == NULL);
    }
    int size() {return N;}
    void insertLast(T item) {
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
    void push(T item) {
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
    T pop() {
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
    T removeLast() {
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
    T peek() {
        return first->val;
    }
    Node<T>* getFirst() {
        return first;
    }
    void setFirst(Node<T>* newFirst) {
        first = newFirst;
    }
    void removeAfter(Node<T>* node) {
        if (node == NULL || node->next == NULL)
            return;
        Node<T>* toRemove = node->next;
        node->next = toRemove->next;
        if (node->next)
            node->next->pre = node;
        else
            last = node;
        delete toRemove;
        --N;
    }
    void insertAfter(Node<T>* node, Node<T>* insert) {
        if (node == NULL || insert == NULL)
            return;
        insert->pre = node;
        insert->next = node->next;
        node->next = insert;
        if (node->next)
            insert->next->pre = insert;
        else
            last = insert;
        ++N;
    }
    void insertBefore(Node<T>* node, Node<T>* insert) {
        if (node == NULL || insert == NULL)
            return;
        insert->pre = node->pre;
        insert->next = node;
        node->pre = insert;
        if (node->pre)
            insert->pre->next = insert;
        else
            first = insert;
        ++N;
    }
    void remove(Node<T>* node) {
        if (node == NULL)
            return;
        if (node->pre == NULL) {
            pop();
            return;
        }
        if (node->next == NULL) {
            removeLast();
            return;
        }

        node->pre->next = node->next;
        node->next->pre = node->pre;
        delete node;
        --N;
    }

private:
    Node<T> * first;
    Node<T> * last;
    int N;
};
