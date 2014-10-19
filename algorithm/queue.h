#include <iostream>

template<typename T>
class queue {
public:
    queue(): first(NULL), last(NULL), N(0) {}
    bool isEmpty() {
        return (first == NULL);
    }
    int size() {return N;}
    void enqueue(T item) {
        Node* oldLast = last;
        last = new Node;
        last->val = item;
        last->next = NULL;
        if (isEmpty())
            first = last;
        else
            oldLast->next = last;
        N++;
    }
    T dequeue() {
        Node* oldFirst = first;
        T item = first->val;
        first = first->next;
        if (isEmpty())
            last = NULL;
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
    Node * last;
    int N;
};
