/* ************************************************************
    * CONFIGURACIÓN DEL ARCHIVO *
   ************************************************************ */

/* --------------- INCLUSIÓN DE HEADERS --------------- */

// Header correspondiente al archivo actual
#include "print_grid.h"


/* ************************************************************
    * FUNCIÓN PARA IMPRIMIR LA RETÍCULA *
   ************************************************************ */

// La función imprime la retícula correspondiente a la generación actual
void print_grid(int grid[HEIGHT][WIDTH])
{
    /* Inicializamos un contador de filas en 0 y lo aumentamos en 1 al terminar de recorrer cada fila, hasta llegar a la 
    fila HEIGHT-1 */
    for(int row = 0; row < HEIGHT; row++)
    {
        // --------------- IMPRESIÓN DE LÍNEA SUPERIOR ---------------

        /* Inicializamos un contador de columnas en 0 y lo aumentamos en 1 al recorrer cada posición en una misma fila, 
        hasta llegar a la posición WIDTH-1 */
        for(int col = 0; col < WIDTH; col++)
        {
            // Imprimimos la línea superior en cada posición de una fila, para todas las filas
            printf("+---");
        }

        // Cerramos la línea superior con un '+' al final de la fila y hacemos un salto de línea
        printf("+ \n");

        // --------------- IMPRESIÓN DE LAS CÉLULAS ---------------

        /* Inicializamos un contador de columnas en 0 y lo aumentamos en 1 al recorrer cada posición en una misma fila, 
        hasta llegar a la posición WIDTH-1 */
        for(int col = 0; col < WIDTH; col++)
        {
            // Separamos cada posición con un delimitador de columna '|'
            printf("| ");

            // Si la célula de la posición actual está viva (su valor es 1), imprimimos un '*'
            if(grid[row][col] == 1)
            {
                printf("* ");
            }

            // Si está vacía (su valor es 0), imprimimos un espacio vacío
            else
            {
                printf("  ");
            }
        }

        // Cerramos la fila con un delimitador final '|'
        printf("| \n");
    }

    // --------------- IMPRESIÓN DE LÍNEA INFERIOR ---------------

    /* Inicializamos un contador de columnas en 0 y lo aumentamos en 1 al recorrer cada posición en una misma fila, 
    hasta llegar a la posición WIDTH-1 */
    for(int col = 0; col < WIDTH; col++)
    {
        // Imprimimos la línea inferior en cada posición de la fila, únicamente para la última fila
        printf("+---");
    }

    // Cerramos la línea inferior con un '+' al final de la fila y hacemos un salto de línea
    printf("+ \n");

    // La función no retorna nada
    return;
}


/* ************************************************************
    * FUNCIÓN PARA COPIAR LA RETÍCULA *
   ************************************************************ */

// La función copia la retícula de la siguiente generación en la retícula actual
void copy_grid(int current_grid[HEIGHT][WIDTH], int next_grid[HEIGHT][WIDTH])
{
    /* Inicializamos un contador de filas en 0 y lo aumentamos en 1 al terminar de recorrer cada fila, hasta llegar a la 
    fila HEIGHT-1 */
    for(int row = 0; row < HEIGHT; row++)
    {
        /* Inicializamos un contador de columnas en 0 y lo aumentamos en 1 al recorrer cada posición en una misma fila, 
        hasta llegar a la posición WIDTH-1 */
        for(int col = 0; col < WIDTH; col++)
        {
            /* Copiamos cada posición de la retícula correspondiente a la siguiente generación en la misma posición
            de la retícula correspondiente a la generación actual */  
            current_grid[row][col] = next_grid[row][col];
        }
    }

    // La función no retorna nada
    return;
}
