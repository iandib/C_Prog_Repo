#include <stdio.h>

void convolucion(double primerVector[], int largoPrimerVector, 
                 double segundoVector[], int largoSegundoVector, 
                 double resultado[], int largoResultado)
{
    // Inicializar el resultado en ceros
    for (int i = 0; i < largoResultado; i++)
    {
        resultado[i] = 0.0;
    }

    // Realizar la convolución
    for (int i = 0; i < largoPrimerVector; i++)
    {
        for (int j = 0; j < largoSegundoVector; j++)
        {
            resultado[i + j] += primerVector[i] * segundoVector[j];
        }
    }
}

int main(void)
{
    // Definir los vectores a convolucionar
    double primerVector[] = {1, 2, -3};  // Primer polinomio: 1 + 2·x - 3·x²
    double segundoVector[] = {7, -5};    // Segundo polinomio: 7 - 5·x
    int largoPrimerVector = 3;  // Longitud del primer vector
    int largoSegundoVector = 2;  // Longitud del segundo vector

    // El tamaño del resultado es largoPrimerVector + largoSegundoVector - 1
    int largoResultado = largoPrimerVector + largoSegundoVector - 1;
    double resultado[5];  // Definimos el arreglo de salida con un tamaño fijo

    // Llamar a la función de convolución
    convolucion(primerVector, largoPrimerVector, segundoVector, largoSegundoVector, resultado, largoResultado);

    // Imprimir el resultado
    printf("Resultado de la convolución: ");
    for (int i = 0; i < largoResultado; i++)
    {
        printf("%.2f ", resultado[i]);
    }
    printf("\n");

    return 0;
}
