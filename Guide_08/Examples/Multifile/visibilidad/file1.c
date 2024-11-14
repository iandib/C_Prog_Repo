/* file1.c */

#include <stdio.h>

void f2(void);
static void f1(void);

int x;
static int y=13;

int main (void)
{
    printf("main()\n");
    printf("x: %d\n", x);
    printf("y: %d\n", y);
    f1();
    f2();
    f2();
    return 0;
}


static void f1(void)
{
    int x = 5;
    printf("f1()\n");
    printf("x: %d\n", x);
    printf("y: %d\n", y);
}
