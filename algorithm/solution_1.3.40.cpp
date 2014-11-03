#include <iostream>
#include "stack.h"

void printStack(stack<std::string>& s) {
    Node<std::string>* curr = s.getFirst();
    while (curr) {
        std::cout << curr->val << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}

int main() {
    std::string val;
    stack<std::string> s;
    Node<std::string>* curr;
    while (std::cin >> val) {
        curr = s.getFirst();
        if (curr && val.compare(curr->val) == 0)
            continue;
        while (curr) {
            if (curr->next == NULL) {
                curr = NULL;
                break;
            } else if (val.compare(curr->next->val) == 0)
                break;
            curr = curr->next;
        }

        if (curr != NULL)
            s.removeAfter(curr);
        s.push(val);
        printStack(s);
    }
    return 0;
}
