#include "linkedMaxPQ.h"
#include "printBinaryTree.h"
#include "binaryTreeNode.h"

int main() {
    size_t i;
    size_t size = 10;
    int a[] = {3, 2, 1, 7, 6, 5, 9, 4, 10, 8};

    linkedMaxPQ<int> pq;
    Node<int>* pq_root;
    for (i = 0; i < size; i++) {
        pq.insert(a[i]);
        if (i == 0)
            pq_root = pq.getRoot();
        print_binary_tree<int>(pq_root, (int)log2(pq.size()) + 1);
    }

    for (i = 0; i < size; i++) {
        print_binary_tree<int>(pq_root, (int)log2(pq.size()) + 1);
        std::cout << pq.delMax() << std::endl;
    }
    for (i = 0; i < size; i++) {
        pq.insert(a[i]);
        if (i == 0)
            pq_root = pq.getRoot();
        print_binary_tree<int>(pq_root, (int)log2(pq.size()) + 1);
    }

    for (i = 0; i < size; i++) {
        print_binary_tree<int>(pq_root, (int)log2(pq.size()) + 1);
        std::cout << pq.delMax() << std::endl;
    }


    return 0;
}
