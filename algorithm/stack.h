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
        ++N;
    }
    T pop() {
        Node<T>* oldFirst = first;
        T item = first->val;
        first = first->next;
        delete oldFirst;
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
        delete toRemove;
        --N;
    }
    void insertAfter(Node<T>* node, Node<T>* insert) {
        if (node == NULL || insert == NULL)
            return;
        insert->next = node->next;
        node->next = insert;
        ++N;
    }
    void remove(const T& val) {
        Node<T>* curr = first;
        Node<T>* toRemove;
        while (curr != NULL && curr->next != NULL) {
            if (curr->next->val == val) {
                toRemove = curr->next;
                curr->next = toRemove->next;
                delete toRemove;
                --N;
            }
            else
                curr = curr->next;
        }
    }

private:
    Node<T> * first;
    int N;
};
