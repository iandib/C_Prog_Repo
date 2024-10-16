#include <stdio.h>

void hanoi(char n, char ori, char aux, char des);

int main(void)
{
    hanoi(3, 'A', 'B', 'C');
    return 0;
}

void hanoi(char n, char ori, char aux, char des)
{
    if (n <= 1)
    {
        printf("%c > %c\n", ori, des);
    }
    else
    {
        hanoi(n-1, ori, des, aux);
        printf("%c > %c\n", ori, des);
        hanoi(n-1, aux, ori, des);
    }
}
