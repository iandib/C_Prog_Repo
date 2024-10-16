#include <stdio.h>

int main(void) 
{
    // Inicializamos un contador en 0 tal que mientras sea menor o igual a 9, se imprime e incrementa su valor
    for (int count = 0; count <= 9; count++) 
    {
        printf("%d \n", count);
    }

    return 0;
}

// Usar un for en lugar de un while es más apropiado si conocemos la cantidad de iteraciones
