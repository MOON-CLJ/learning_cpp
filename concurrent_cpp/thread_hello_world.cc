#include <iostream>
#include <thread>

void hello()
{
    std::cout << "thread hello world" << std::endl;
}

int main()
{
    std::thread t(hello);
    t.join();
}
