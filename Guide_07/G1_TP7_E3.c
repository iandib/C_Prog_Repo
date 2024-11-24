#include <stdio.h>

int suma_digitos(int n)
{
    // Caso base
    if (n == 0)
    {
        // Devuelve 0 cuando no quedan dígitos
        return 0; 
    }

    // Llamada recursiva: suma el último dígito con la suma de los demás
    return (n % 10) + suma_digitos(n / 10);
}

int main(void)
{
    int num = 9999;

    // Imprime el resultado de la suma de los dígitos
    printf("%d\n", suma_digitos(num));

    return 0;
}
