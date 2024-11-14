#include <stdio.h>

void swap(int*, int*);

int main(void)
{
    int izq = 9, der = 5;
    printf("izq: %d, der: %d\n", izq, der);
    
    swap(&izq, &der);
    printf("izq: %d, der: %d\n", izq, der);
    
    return 0;
}

void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

