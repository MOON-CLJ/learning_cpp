#include <cmath>
#include <iomanip>

#include "queue.h"
#include "binaryTreeNode.h"


template<typename T>
void print_binary_tree(Node<T>* root, int height) {
    if (!root)
        return;
    std::cout << "-->" << std::endl;
    queue<Node<T>*> bqueue;
    bqueue.enqueue(root);
    int node_width = 5;
    int curr_level_num = 1;
    int next_level_num = 0;
    int level = 1;
    int padding = node_width * (std::pow(2, height - level) - 1);
    std::cout << std::setw(padding / 2) << "";
    while (level <= height) {
        std::cout << std::setw(node_width);
        Node<T>* currNode = bqueue.dequeue();
        --curr_level_num;
        if (currNode) {
            std::cout << std::setw(2) << currNode->val;
            std::cout << std::setw(1) << "|";
            std::cout << std::setw(2) << (currNode->ancestor ? currNode->ancestor->val : -1);
            bqueue.enqueue(currNode->lchild);
            bqueue.enqueue(currNode->rchild);
        } else {
            bqueue.enqueue(NULL);
            bqueue.enqueue(NULL);
        }
        next_level_num += 2;
        std::cout << std::setw(padding) << "";
        if (curr_level_num == 0) {
            curr_level_num = next_level_num;
            next_level_num = 0;
            ++level;
            padding = node_width * (std::pow(2, height - level) - 1);
            std::cout << std::endl << std::setw(padding / 2) << "";
        }
    }
}
