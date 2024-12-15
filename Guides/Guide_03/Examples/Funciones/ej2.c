#include <stdio.h>

void fun1(void);
void fun2(void);
int n1 = 1;

int main (void)
{
    int n1 = 2;
    {
        int n1 = 3;
        printf("%d ", n1);
        fun1();
        fun2();
    }
    printf("%d\n", n1);
    return 0;
}

void fun1(void)
{
   int n1=4;
   printf("%d ", n1);
}

void fun2(void)
{
   printf("%d ", n1);
}

