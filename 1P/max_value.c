#include <stdio.h>

// Prototipo de la función
long int* find_max_element(long int* array, int array_length);

int main() 
{
    // Arreglo de prueba
    long int test_array[] = {10, 50, 30, 70, 20};
    
    // Llamamos a la función
    long int* max_element = find_max_element(test_array, 5);
    
    // Comprobamos si la función devolvió un puntero válido
    if (max_element != NULL) 
    {
        printf("The largest element in the array is: %ld\n", *max_element);
    } 
    else 
    {
        printf("Invalid input or empty array.\n");
    }

    return 0;
}

// Definición de la función
long int* find_max_element(long int* array, int array_length) 
{
    // Validamos si el arreglo es NULL o su longitud es 0
    if (array == NULL || array_length <= 0) 
    {
        return NULL;
    }

    // Inicializamos el puntero al mayor valor como el primer elemento del arreglo
    long int* max_element_ptr = &array[0];

    // Recorremos el arreglo para encontrar el valor máximo
    for (int array_index = 1; array_index < array_length; array_index++) 
    {
        if (array[array_index] > *max_element_ptr) 
        {
            // Actualizamos el puntero si encontramos un valor mayor
            max_element_ptr = &array[array_index];
        }
    }

    // Devolvemos el puntero al mayor elemento
    return max_element_ptr;
}
