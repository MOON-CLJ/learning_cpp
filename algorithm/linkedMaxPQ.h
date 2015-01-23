#include <iostream>
#include <bitset>
#include <math.h>
#include <iomanip>
#include "binaryTreeNode.h"

template<typename T>
class linkedMaxPQ {
public:
    linkedMaxPQ(): pq_root(NULL), last_left_node(NULL), N(0) {}
    bool isEmpty() {
        return N == 0;
    }
    size_t size() { return N; }
    void insert(T v) {
        ++N;
        if (N == 1) {
            Node<T>* newNode = new Node<T>;
            newNode->val = v;
            newNode->ancestor = NULL;
            newNode->lchild = NULL;
            newNode->rchild = NULL;
            pq_root = newNode;
        } else if (N % 2 == 0) {
            std::bitset<32> bset(N);
            const size_t bset_size = (size_t)ceil(log2(N + 1));
            Node<T>* tmp = pq_root;
            for (size_t i = bset_size - 2; i > 0; i--)
                tmp = (bset[i]) ? tmp->rchild : tmp->lchild;

            Node<T>* newNode = new Node<T>;
            newNode->val = v;
            newNode->ancestor = tmp;
            newNode->lchild = NULL;
            newNode->rchild = NULL;
            tmp->lchild = newNode;
            last_left_node = newNode;
            swin(newNode);
        } else {
            Node<T>* ancestorNode = last_left_node->ancestor;
            Node<T>* newNode = new Node<T>;
            newNode->val = v;
            newNode->ancestor = ancestorNode;
            newNode->lchild = NULL;
            newNode->rchild = NULL;
            ancestorNode->rchild = newNode;
            swin(newNode);
        }
    }
    T delMax() {
        T max = pq_root->val;
        --N;
        if (N == 0) {
            pq_root = NULL;
            return max;
        }

        std::bitset<32> bset(N + 1);
        const size_t bset_size = (size_t)ceil(log2(N + 2));
        Node<T>* tmp = pq_root;
        for (size_t i = bset_size - 2; i > 0; i--)
            tmp = (bset[i]) ? tmp->rchild : tmp->lchild;
        Node<T>* toDel = bset[0] ? tmp->rchild : tmp->lchild;
        exch(toDel, pq_root);
        if (bset[0])
            tmp->rchild = NULL;
        else
            tmp->lchild = NULL;
        delete toDel;
        sink(pq_root);
        return max;
    }
    Node<T>* getRoot() {
        return pq_root;
    }

private:
    Node<T>* pq_root;
    Node<T>* last_left_node;
    size_t N;

    bool less(Node<T>* i, Node<T>* j) {
        return i->val < j->val;
    }
    void exch(Node<T>* i, Node<T>* j) {
        T tmp = i->val;
        i->val = j->val;
        j->val = tmp;
    }
    void swin(Node<T>* x) {
        Node<T>* tmp = x;
        while (tmp->ancestor && less(tmp->ancestor, tmp)) {
            exch(tmp->ancestor, tmp);
            tmp = tmp->ancestor;
        }
    }
    void sink(Node<T>* x) {
        Node<T>* tmp = x;
        Node<T>* larger_child = NULL;
        while (tmp->lchild) {
            larger_child = tmp->rchild && less(tmp->lchild, tmp->rchild) ? tmp->rchild : tmp->lchild;
            if (!less(tmp, larger_child)) break;
            exch(tmp, larger_child);
            tmp = larger_child;
        }
    }
};
