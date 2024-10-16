#include <stdio.h>

int main (void)
{
    int num = 4;

    switch (num)
    {
    case 1:
    case 3:
    case 4+1:
        printf("impar\n");
        break;
    case 2:
    case 2*2:
        printf("par\n");
        break;
    default:
        printf("otro caso\n");
        break;
    }

    return 0;
}
