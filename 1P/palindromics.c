#include <stdio.h>

int is_capicua(int* p1, unsigned int lenght)
{
    // Defino una variable para el índice del array a recorrer
    int array_index;

    // Reviso si el largo del arreglo es válido
    if (lenght < 3)
    {
        printf("Palindromic numbers have 3 or more digits.\n");
        return -1;
    }
    
    // Comparar elementos desde el inicio hasta la mitad del arreglo
    for (array_index = 0; array_index < lenght / 2; array_index++)
    {
        // Si el número en la posición array_index no es igual al de la posición (lenght - 1 - array_index), retorno -1
        if (*(p1 + array_index) != *(p1 + lenght - 1 - array_index))
        {
            return -1;
        }
    }

    // Si el número es capicúa, retorno 0
    return 0;
}

int main(void)
{
    // Defino un número de prueba
    int array[] = {4, 2, 7};

    // Calculo el tamaño del arreglo
    int lenght = sizeof(array)/sizeof(array[0]);

    // Llamo a la función is_capicua para determinar si es o no capicúa
    if (is_capicua(array, lenght) == 0)
    {
        printf("It is a palindromic number \n");
    }
    else
    {
        printf("It is not a palindromic number \n");
    }

    return 0;
}
