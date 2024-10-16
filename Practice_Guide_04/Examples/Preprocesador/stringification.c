#include <stdio.h>
#include <stdlib.h>

#define CHECK(s) if(s) printf("Error: "#s"\n");

int main(void)
{
    int x;
    printf("Hello " "world!\n"); // se pueden concatenar strings

    for(x=0;x<10;x++)
    {
        printf("x=%d\n",x);
        CHECK(x==3);
        CHECK(x%4==0);
    }

    return 0;
}
