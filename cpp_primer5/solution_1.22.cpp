#include <iostream>
#include "Sales_item.h"

int main()
{
    Sales_item total, tmp;
    std::cin >> total;
    while (std::cin >> tmp) 
    {
        total += tmp;
    }
    std::cout << total << std::endl;
}
