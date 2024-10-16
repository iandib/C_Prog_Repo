#include <stdio.h>

int main(void)
{
    int arr[] = { 10, 20, 30 };
    int *p;
    p = arr;

    printf("*(p+1): %d\n", *(p+1));
    printf("*(p+2): %d\n", *(p+2));
    printf("*p+1: %d\n", *p+1);
    
    printf("p: %p, *p: %d\n", p, *p);
    *p++ = 3;
    printf("p: %p, *p: %d\n", p, *p);
    (*p)++;
    printf("p: %p, *p: %d\n", p, *p);
    
    return 0;
}

