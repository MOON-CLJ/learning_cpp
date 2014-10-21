#include <iostream>

int main(){
   long* a;
   long** b = &a;
   std::cout << "address of a = " << &a << std::endl;
   std::cout << "value of a = " << a << std::endl;
   a = (long *) b;
   std::cout << "address of a = " << &a << std::endl;
   std::cout << "value of a = " << a << std::endl;
   std::cout << (long) a << std::endl;
   std::cout << *a << std::endl;
   std::cout << *((long *) *a) << std::endl;
   return 0;
}
