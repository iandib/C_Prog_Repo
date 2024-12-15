#include <stdio.h>

int suma(char, char);

int main(void) 
{
    unsigned char n1 = 129 , n2 = 1;
    int rta;
    rta = suma(n1, n2);
    printf("%d", rta);
    return 0;
}

int suma(char a, char b)
{
    int resultado;
    resultado = a + b;
    return resultado;
}
