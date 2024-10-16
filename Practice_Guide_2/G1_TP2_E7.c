#include <stdio.h>

int main(void) 
{
    // Definimos la cantidad de filas y de columnas, respectivamente
    unsigned int m = 51, n = 42;

    // Definimos una variable para el primer valor de cada fila
    unsigned int initial_val;

    // Definimos un contador de la cantidad de filas y otro para la cantidad de columnas, respectivamente
    unsigned int count_m, count_n;

    // Definimos una variable para producir el incremento de arriba a abajo que debe tener la matriz
    unsigned int inc = 1;

    // Inicializamos el contador de filas en 1 y lo aumentamos en 1 al terminar de imprimir cada fila, hasta completar toda la matriz
    for (count_m = 1; count_m <= m; count_m++)
    {
        /* Inicializamos el primer valor de cada fila en 0 y lo aumentamos en 1 al recorrer cada posición siguiente, produciendo el incremento de izquierda a derecha
        Además, inicializamos el contador de columnas en 1 y lo aumentamos en 1 al recorrer cada posición en la fila */
        for (initial_val = 0, count_n = 1; count_n <= n; initial_val++, count_n++)
        {
            /* Al imprimir cada valor tenemos en cuenta el correspondiente incremento de arriba a abajo, y además le damos un ancho fijo de 3 caracteres 
            para que todas las columnas queden alineadas */
            printf("%3d ", initial_val + inc);
        }

        printf("\n");

        // Tras imprimir cada fila, aumentamos en 1 el incremento de arriba a abajo a aplicar
        inc++;
    }

    return 0;
}
