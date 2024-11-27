#include <stdio.h>
#include <stdlib.h>

// Definimos la estructura vecgen_t con un puntero a un arreglo de floats
typedef struct
{
    // Puntero a un arreglo de floats
    float (*vec)[]; 

    // Largo actual del arreglo
    int length;     
} vecgen_t;


// Función para eliminar un elemento del vector en un índice específico
int eliminar_elemento(vecgen_t *pvec, int index)
{
    // Validar que la estructura no sea nula
    if (pvec == NULL)
    {
        return -1; 
    }

    // Si el vector es nulo o de longitud 0, no hay nada que eliminar
    if ((pvec->vec == NULL) || (pvec->length <= 0))
    {
        return -1;
    }

    // Validar índice dentro del rango
    if ((index < 0) || (index >= pvec->length))
    {
        return -1;
    }

    // Mover los elementos posteriores al índice hacia atrás
    for (int i = index; i < (pvec->length - 1); i++)
    {
        (*pvec->vec)[i] = (*pvec->vec)[i + 1];
    }

    // Reducir el tamaño del vector usando realloc
    float (*nuevo_vec)[] = realloc(pvec->vec, sizeof(float) * (pvec->length - 1));

    // Manejo de errores en realloc
    if ((nuevo_vec == NULL) && ((pvec->length - 1) > 0)) 
    {
        return -1; 
    }

    // Actualizar el puntero del vector
    pvec->vec = nuevo_vec;

    // Actualizar el largo del vector
    pvec->length -= 1; 

    return 0;
}


// Función de comparación para qsort
int comparar_floats(const void *a, const void *b)
{
    // Convertimos los punteros genéricos a punteros a float
    float fa = *(const float *)a;
    float fb = *(const float *)b;

    // Devolver 1 si el segundo es mayor que el primero (deben cambiarse de orden)
    if (fb > fa)
    {
        return 1;
    }

    // Devolver 0 si son iguales o si el primero es mayor (no deben cambiarse de orden)
    return 0;
}


void ordenar_vector(vecgen_t *pvec)
{
    // Validar que el vector no sea nulo y tenga elementos
    if ((pvec == NULL) || (pvec->vec == NULL) || (pvec->length <= 0))
    {
        return;
    }

    // Llamar a qsort para ordenar el vector
    qsort(*pvec->vec, pvec->length, sizeof(float), comparar_floats);
}
