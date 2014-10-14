#include <iostream>
#include <vector>

class fixedCapacityStackOfStrings {
public:
    fixedCapacityStackOfStrings(int cap);

    int size();
    bool isEmpty();
    void push(std::string item);

private:
    int n;
    std::vector<std::string> s;
};
