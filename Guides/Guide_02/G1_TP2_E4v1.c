#include <stdio.h>

int main(void) 
{
    // Inicializamos un contador en 0
    int count = 0;

    /* Mientras el contador sea menor o igual a 9, el bucle se ejecuta
    imprimiendo el valor de count y luego sumándole 1 */
    while (count <= 9) 
    {
        printf("%d \n", count);
        count++;
    }

    return 0;
}
