#include <iostream>

template<typename T>
class circularQueue {
public:
    circularQueue(): last(NULL), N(0) {}
    bool isEmpty() {
        return (last == NULL);
    }
    int size() {return N;}
    void enqueue(T item) {
        Node* newNode = new Node;
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
        N++;
    }
    T dequeue() {
        Node* oldFirst = last->next;
        T item = oldFirst->val;
        if (last->next == last)
            last = NULL;
        else
            last->next = last->next->next;
        delete oldFirst;
        N--;
        return item;
    }

private:
    struct Node {
        T val;
        Node * next;
    };
    Node * last;
    int N;
};
