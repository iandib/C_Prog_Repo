#include <stdio.h>

void fun(int n)
{
    // Caso base: si 'n' es menor a 3, se imprime su valor como carácter
    if (n < 3)
    {
        putchar('0' + n);
        putchar(' ');
    }

    // Caso recursivo: descompone 'n' en dos llamadas recursivas
    else
    {
        fun(n-1);
        fun(n-3);
    }
}


int main(void)
{
    // Imprime '2 0 1 2 2 0 2 0 1'
    fun(7);
    return 0;
}
