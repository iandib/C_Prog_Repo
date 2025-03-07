#include <stdio.h>

// Defino una variable global para guardar el resultado del producto escalar
float result = 0;


int vec_prod(float* vec1, float* vec2, int vec_length1, int vec_length2)
{
    // Verificamos si ambos vectores tienen el mismo tamaño
    if (vec_length1 != vec_length2)
    {
        printf("Error: Vectors of different size. \n");
        return 0;
    }   

    // Itero sobre cada elemento de ambos vectores
    for (int index = 0; index < vec_length1; index++)
    {
        // Calculo el producto escalar sumando el producto de cada par de elementos
        result += (vec1[index] * vec2[index]);
    }

    // Retorno 1 si no hubo problemas
    return 1;
}


int main(void)
{
    // Defino vectores de ejemplo
    float vec1[] = {10, 20, 30};
    float vec2[] = {33, 42, 15};

    // Calculo el largo de ambos vectores
    int vec_length1 = sizeof(vec1) / sizeof(vec1[0]);
    int vec_length2 = sizeof(vec2) / sizeof(vec2[0]);

    // Llamo a la función que calcula el producto escalar
    vec_prod(vec1, vec2, vec_length1, vec_length2);

    // Si no hubo error, imprimo el resultado del producto escalar
    if (vec_prod)
    {
        printf("El producto escalar es: %.2f \n", result);
    }

    return 0;
}
