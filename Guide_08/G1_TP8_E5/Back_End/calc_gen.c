/* ************************************************************
    * CONFIGURACIÓN DEL ARCHIVO *
   ************************************************************ */

/* --------------- LLAMADA A HEADERS --------------- */

// Header correspondiente al archivo actual
#include "calc_gen.h"

/* --------------- PROTOTIPOS DE FUNCIONES --------------- */

// La función cuenta cuántos vecinos vivos tiene la célula en la posición (row, col) de la generación actual
static int count_live_neighbors(int grid[HEIGHT][WIDTH], int row, int col);


/* ************************************************************
    * FUNCIÓN PARA CALCULAR LA SIGUIENTE GENERACIÓN *
   ************************************************************ */

// La función calcula la siguiente generación que debe imprimirse a partir de la generación actual y de las reglas del juego
void next_generation(int current_grid[HEIGHT][WIDTH], int next_grid[HEIGHT][WIDTH])
{
    // --------------- ANÁLISIS DE TODAS LAS POSICIONES EN LA RETÍCULA ---------------

    /* Inicializamos un contador de filas en 0 y lo aumentamos en 1 al terminar de recorrer cada fila, hasta llegar a la 
    fila HEIGHT-1 */
    for(int row = 0; row < HEIGHT; row++)
    {
        /* Inicializamos un contador de columnas en 0 y lo aumentamos en 1 al recorrer cada posición en una misma fila, 
        hasta llegar a la posición WIDTH-1 */
        for(int col = 0; col < WIDTH; col++)
        {
            // Contamos cuántos vecinos vivos tiene la célula en la posición (row, col)
            int live_neighbors = count_live_neighbors(current_grid, row, col);

            // --------------- APLICACIÓN DE LAS REGLAS DEL JUEGO ---------------

            // Si la célula en la posición (row, col) está viva (su valor es 1)
            if(current_grid[row][col] == 1)
            {
                // Si tiene menos de 2 vecinos vivos, muere por subpoblación (su valor pasa a ser 0)
                if(live_neighbors < 2)
                {
                    next_grid[row][col] = 0;
                }

                // Si tiene más de 3 vecinos vivos, muere por sobrepoblación (su valor pasa a ser 0)
                else if(live_neighbors > 3)
                {
                    next_grid[row][col] = 0;
                }

                // Si tiene exactamente 2 o 3 vecinos, sobrevive (su valor se mantiene en 1)
                else
                {
                    next_grid[row][col] = 1;
                }
            }

            // Si, en cambio, la posición (row, col) está vacía (su valor es 0)
            else
            {
                // Si tiene exactamente 3 vecinos, nace una célula (su valor pasa a ser 1)
                if(live_neighbors == 3)
                {
                    next_grid[row][col] = 1;
                }

                // En cualquier otro caso, la posición sigue vacía (su valor se mantiene en 0)
                else
                {
                    next_grid[row][col] = 0;
                }
            }
        }
    }

    // No es necesario que la función retorne las actualizaciones porque estas ya se guardan en el array original
    return;
}


/* ************************************************************
    * FUNCIÓN PARA CONTAR LOS VECINOS VIVOS DE UNA CÉLULA *
   ************************************************************ */

// La función cuenta cuántos vecinos vivos tiene la célula en la posición (row, col) de la retícula actual
static int count_live_neighbors(int grid[HEIGHT][WIDTH], int row, int col)
{
    // Definimos una variable que almacenará el número de vecinos vivos
    int live_neighbors = 0;

    // Definimos una variable que almacenará el desplazamiento en una misma columna desde la posición (row, col)
    int row_displacement;

    // Definimos una variable que almacenará el desplazamiento en una misma fila desde la posición (row, col)
    int col_displacement;

    // --------------- ANÁLISIS DE ÁREA (3X3) ALREDEDOR DE LA CÉLULA ---------------

    // Recorremos las tres columnas que van desde 1 lugar a la izquierda de (row, col) hasta 1 lugar a su derecha
    for(row_displacement = -1; row_displacement <= 1; row_displacement++)
    {
        // Y repetimos lo anterior para las tres filas que van desde 1 lugar abajo de (row, col) hasta 1 lugar arriba suyo
        for(col_displacement = -1; col_displacement <= 1; col_displacement++)
        {
            // Si estamos en la posición actual (la célula misma), la omitimos
            if(row_displacement == 0 && col_displacement == 0)
            {
                continue;
            }

            // --------------- CONTADOR DE CÉLULAS VIVAS ---------------

            // Calculamos las coordenadas de cada célula vecina (se actualiza con cada valor de x e y en el recorrido de 3x3)
            int neighbor_row = row + row_displacement;
            int neighbor_col = col + col_displacement;

            /* Verificamos si las coordenadas de la célula vecina están dentro de los límites de la retícula (desde la posición 0
            hasta la posición N-1) */
            if((neighbor_row >= 0) && (neighbor_row < HEIGHT) && (neighbor_col >= 0) && (neighbor_col < WIDTH))
            {
                /* Si la célula vecina está viva (el valor de la posición (neighbor_row, neighbor_col) de la retícula es 1), 
                aumentamos el contador de células vivas en 1 */
                if(grid[neighbor_row][neighbor_col] == 1)
                {
                    live_neighbors++;
                }
            }
        }
    }

    // Retornamos el número total de vecinos vivos
    return live_neighbors;
}
