#include <stdio.h>
#include <stdlib.h>

#define DECIR(s) decir_ ## s ## _f()

void decir_hola_f(void)
{
    printf("Hola!\n");
}
void decir_chau_f(void)
{
    printf("Chau!\n");
}



int main(void)
{
    int x;
    DECIR(hola);
    DECIR(chau);

    return 0;
}
