#include <stdio.h>

/* Si omito el último return en is_capicua, el valor devuelto en el caso base (o en el caso de error) no es propagado hacia los casos anteriores, 
por lo que el comportamiento de la función es indeterminado */

#define MAX_LEN 5

// Función recursiva para verificar si un arreglo es capicúa
int is_capicua(int* p1, int* p2)
{
    // Caso base: los punteros se encuentran o se cruzan
    if (p1 >= p2)
    {
        // Es capicúa
        return 1; 
    }

    // Verificar si los extremos actuales son iguales
    if (*p1 != *p2)
    {
        // No es capicúa
        return 0; 
    }

    // Llamada recursiva para el siguiente par de extremos
    return is_capicua(p1 + 1, p2 - 1);
}

int main(void)
{
    int arr[MAX_LEN] = {3, 2, 7, 2, 3};

    int* p1 = &arr[0];
    int* p2 = &arr[MAX_LEN - 1];

    if (is_capicua(p1, p2))
    {
        printf("Es capicua \n");
    }

    else
    {
        printf("No es capicua \n");
    }

    return 0;
}
