#include <stdio.h>

int main (void)
{
    int count=10;
    printf("%d\n",count);

    for (count=0 ; count<4 ; count++)
    {
        printf("%d\n",count);
    }
    printf("fin\n");
    printf("%d\n",count);

    return;
}

