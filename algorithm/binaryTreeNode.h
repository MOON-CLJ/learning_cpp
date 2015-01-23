#ifndef BINARY_TREE_NODE
#define BINARY_TREE_NODE
template<typename T>
struct Node {
    T val;
    Node<T>* ancestor;
    Node<T>* lchild;
    Node<T>* rchild;
};
#endif
