#include <stdio.h>

int main(void) 
{
    // Definimos el número a analizar
    unsigned int num = 14983;

    // Definimos una variable que guardará los posibles divisores del número
    unsigned int div;

    // Definimos un contador de divisores y lo inicializamos en 0
    unsigned int div_count = 0;

    /* Inicializamos el divisor en 1 y lo aumentamos en 1 luego de cada ejecución del bloque, 
    hasta que su valor sea igual al del número que analizamos */
    for(div = 1; div <= num; div++) 
    {
        // Evaluamos si el número es divisible por el divisor actual
        if(num % div == 0)
        {
            // Si es el caso, aumentamos el contador de divisores en 1
            div_count++;
        }
    }

    // Si el número tiene exactamente 2 divisores, es primo
    if(div_count == 2)
    {
        printf("El numero %d es un numero primo \n", num);
    }
    
    // Si tiene más divisores, no es primo
    else
    {
        printf("El numero %d no es un numero primo \n", num);
    }

    /*
    Opcionalmente, podemos imprimir la cantidad de divisores que tiene el número:
    printf("El numero %d tiene %d divisores \n", num, div_count);
    */

    return 0;
}
