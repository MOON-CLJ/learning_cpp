#include <iostream>

struct Node {
    int val;
    Node * next;
};

int main() {
    Node * head = NULL;
    int i;
    for(i=1;i<=10;i++) {
        Node * curr = new Node;
        curr->val = i;
        curr->next  = head;
        head = curr;
    }
    while(head) {
        std::cout << head->val << " ";
        head = head->next ;
    }
    std::cout << std::endl;
    return 0;
}
