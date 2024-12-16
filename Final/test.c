#include <stdio.h> 
void fuu(int a); 
int mat[] = {-3, -9, -5}; 
int main(void) 
{ 
   int *p = mat+1; 
   fuu(*p++); 
} 
void fuu(int a) 
{ 
   printf("%d\n", a); 
}