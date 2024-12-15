#include <stdio.h>

int suma (int, int);

int main (void)
{
    int rta, n1=500, n2=6000; // creo variables
    
    printf("n1: %d ; n2: %d ; ", n1, n2); // Imprimo su valor inicial
    printf("rta: %d\n", rta);
    
    rta = suma(n1, n2); // llamada a función

    printf("n1: %d ; n2: %d ; ", n1, n2); // Imprimo su valor final
    printf("rta: %d\n", rta);
    
    return 0;
}


int suma (int a , int b)
{
    int resultado;
    resultado = a + b; // operación de la función
    return resultado;  // devuelvo el resultado
}
