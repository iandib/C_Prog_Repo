#include <stdio.h>

int main(void)
{
    int y = 5;
    float x = -3.25;

    while (y -= 1)
    {
        printf("%d \n", y);
    }

    printf("%010f", x);

    return 0;
}