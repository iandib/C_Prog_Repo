#include <stdio.h>

int main(void)
{
    int x;
    int *px;
    
    x = 4660;
    px = &x;
    
    printf("x = %X\n", x);
    printf("px = %p\n", px);
    printf("&px = %p\n", &px);
    
    return 0;
}
