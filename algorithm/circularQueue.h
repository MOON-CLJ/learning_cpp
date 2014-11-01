#include <iostream>

template<typename T>
struct Node {
    T val;
    Node<T> * next;
};

template<typename T>
class circularQueue {
public:
    circularQueue(): last(NULL), N(0) {}
    bool isEmpty() {
        return (last == NULL);
    }
    int size() {return N;}
    void enqueue(T item) {
        Node<T>* newNode = new Node<T>;
        newNode->val = item;
        if (isEmpty()) {
            last = newNode;
            last->next = last;
        }
        else {
            newNode->next = last->next;
            last->next = newNode;
            last = last->next;
        }
        ++N;
    }
    T dequeue() {
        Node<T>* oldFirst = last->next;
        T item = oldFirst->val;
        if (last->next == last)
            last = NULL;
        else
            last->next = last->next->next;
        delete oldFirst;
        --N;
        return item;
    }
    Node<T>* getLast() {
        return last;
    }
    void removeAfter(Node<T>* node) {
        if (node == NULL)
            return;
        Node<T>* toRemove = node->next;
        if (node == node->next) {
            last = NULL;
        } else if (toRemove == last) {
            node->next = last->next;
            last = node;
        } else {
            node->next = toRemove->next;
        }

        delete toRemove;
        --N;
    }

private:
    Node<T> * last;
    int N;
};
