/* File2.c */
#include <stdio.h>

static void f3(void);

int y = 27;

void f2 (void)
{
    int x = 5;
    printf("f2()\n");
    printf("x: %d\n", ++x);
    printf("y: %d\n", ++y);
    f3();
}

static void f3(void)
{
    static int x = 99;
    printf("f3()\n");
    printf("x: %d\n", ++x);
    printf("y: %d\n", ++y);
}
