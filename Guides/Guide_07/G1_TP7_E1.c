#include <stdio.h>

/* La llamada recursiva no es con return poorque la función no devuelve nada (es de tipo void) */

void dec2bin(unsigned int n)
{
    // Caso base
    if (n == 0)
    {
        return;
    }

    // Llamada recursiva
    dec2bin(n/2);
    printf("%d", n % 2);
}

int main(void)
{
    unsigned int num = 28;
    dec2bin(num);
    printf("\n");
    return 0;
}