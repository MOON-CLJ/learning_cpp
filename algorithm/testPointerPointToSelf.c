#include<stdio.h>

int main(){
   int* a;
   int b = (int)&a;
   a = b;
   printf("address of a = %d\n", &a);
   printf("  value of a = %d\n", a);
}
