#include <vector>

#include "FixedCapacityStackOfStrings.h"

fixedCapacityStackOfStrings::fixedCapacityStackOfStrings(int cap) : s(cap), n(0) {}
int fixedCapacityStackOfStrings::size() {return n;}
bool fixedCapacityStackOfStrings::isEmpty() {return n == 0;}
void fixedCapacityStackOfStrings::push(std::string item) {
}
