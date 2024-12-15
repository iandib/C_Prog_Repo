#include <stdio.h>

#define CANT_BITS_NUM   (sizeof(unsigned int)*8)

int main (void)
{
    unsigned int mynum = 23564;
    unsigned int mymask;

    printf("Numero decimal: %u\n", mynum); // imprimo el número en formato DECIMAL
    printf("Numero hexadecimal: 0x%X\n", mynum); // imprimo el número en formato HEXADECIMAL
    printf("Numero binario: 0b"); // encabezado binario

    for (mymask = 1<<(CANT_BITS_NUM-1) ; mymask ; mymask >>= 1)
    {
        printf("%d", (mynum & mymask) != 0);
    }

    printf("\n"); // nueva linea final

    return 0;
}
