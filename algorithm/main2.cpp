#include <iostream>

#include "stack.h"

int main() {
    std::string str[17] = {"it", "was", "-", "the", "best", "-", "of", "times", "-",
        "-", "-", "it", "was", "-", "the", "-", "-"};
    stack<std::string> mystack;
    for (int i = 0; i < 17; i++) {
        if (str[i].compare("-") == 0)
            std::cout << mystack.pop() << std::endl;
        else
            mystack.push(str[i]);
    }
    return 0;
}
