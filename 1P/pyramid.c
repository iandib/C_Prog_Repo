/* ************************************************************
    * CONFIGURACIÓN GENERAL *
   ************************************************************ */

/* --------------- LIBRERÍAS UTILIZADAS --------------- */

// Librería estándar de entrada y salida en C
#include <stdio.h>

/* --------------- PARÁMETROS Y VARIABLES --------------- */

// Defino una constante para la dimensión de la pirámide
#define PYRAMID_SIZE 7

/* --------------- PROTOTIPOS DE LAS FUNCIONES --------------- */

// La función calcula el valor absoluto de un número (la uso porque no nos dejan usar la librería math.h)
int calc_abs(int num);

// La función imprime la pirámide dada su dimensión (n)
void pyramid(int n);

// La función calcula la distancia máxima de cada celda (row, col) al centro de la pirámide
int calc_dist(int n, int row, int col);

// La función devuelve el índice central de la matriz (o el rango si n es par)
void find_center(int n, int* center_start, int* center_end);


/* ************************************************************
    * FUNCIÓN PRINCIPAL *
   ************************************************************ */

int main()
{
    // Llamo a la función para imprimir la pirámide con la constante PYRAMID_SIZE
    pyramid(PYRAMID_SIZE);
    return 0;
}


/* ************************************************************
    * FUNCIÓN PARA CALCULAR VALOR ABSOLUTO *
   ************************************************************ */

// La función calcula el valor absoluto de un número (la uso porque no nos dejan usar la librería math.h)
int calc_abs(int num)
{
    return (num > 0) ? num : -num;
}


/* ************************************************************
    * FUNCIÓN PARA IMPRIMIR LA PIRÁMIDE *
   ************************************************************ */

// La función imprime la pirámide dada su dimensión (n)
void pyramid(int n)
{
    // Defino una variable para calcular la distancia máxima que puede tener una celda a su centro
    int max_dist = ((n - 1) / 2);

    // Inicializo el contador de filas en 1 y lo aumentamos en 1 al terminar de imprimir cada fila, hasta completar toda la pirámide
    for (int row = 1; row <= n; row++)
    {
        // Inicializo el contador de columnas en 1 y lo aumentamos en 1 al terminar de imprimir cada posición en una fila, hasta completar toda la fila
        for (int col = 1; col <= n; col++)
        {
            // Calculo la distancia de la celda actual al centro de la pirámide
            int dist = calc_dist(n, row, col);
            
            /* --------------- IMPRESIÓN DE CADA POSICIÓN --------------- */

            // La explicación del ajuste está en las notas iniciales

            if (n % 2 == 0)
            {
                // Si la pirámide tiene dimensiones pares, sumo 2 para hacer el ajuste de los bordes
                printf("%d ", (max_dist - dist + 2));
            }

            else
            {
                // Si la pirámide tiene dimensiones impares, sumo 1 para hacer el ajuste de los bordes
                printf("%d ", (max_dist - dist + 1));
            }
        }

        // Hago un salto de línea para cambiar de fila
        printf("\n");
    }

    // La función no retorna nada
    return;
}


/* ************************************************************
    * FUNCIÓN PARA CALCULAR DISTANCIA AL CENTRO *
   ************************************************************ */

// La función calcula la distancia máxima de cada celda (row, col) al centro de la pirámide
int calc_dist(int n, int row, int col)
{
    // Defino dos variables para guardar la posición del centro de la pirámide (donde inicia y donde termina)
    int center_start, center_end;

    /* Llamo a la función find_center para encontrar el centro de la pirámide, le paso un puntero a las variables que acabo de definir
    para poder modificarlas directamente */
    find_center(n, &center_start, &center_end);

    /* --------------- DISTANCIA A LA FILA DEL CENTRO --------------- */

    // Me quedo con la mayor distancia (valor absoluto) entre la fila actual y la fila correspondiente al inicio o fin del centro
    int dist_row = (calc_abs(row - center_start) > calc_abs(row - center_end)) ?
                    calc_abs(row - center_start) : 
                    calc_abs(row - center_end);

    /* --------------- DISTANCIA A LA COLUMNA DEL CENTRO --------------- */

    // Me quedo con la mayor distancia (valor absoluto) entre la columna actual y la columna correspondiente al inicio o fin del centro
    int dist_col = (calc_abs(col - center_start) > calc_abs(col - center_end)) ?
                    calc_abs(col - center_start) :
                    calc_abs(col - center_end);

    /* --------------- SELECCIÓN DE DISTANCIA MÁXIMA --------------- */

    // Retorno la mayor distancia al centro (entre filas y columnas) desde la celda actual
    return (dist_row > dist_col) ? dist_row : dist_col;
}


/* ************************************************************
    * FUNCIÓN PARA DETECTAR EL CENTRO DE LA PIRÁMIDE *
   ************************************************************ */

// La función devuelve el índice central de la matriz (o el rango si n es par)
void find_center(int n, int* center_start, int* center_end)
{
    // Si n es par, el centro está en un rango de dos posiciones
    if (n % 2 == 0)
    {
        // Tomo el inicio del centro como el entero que resulta de dividir la dimensión de la pirámide entre 2
        *center_start = (n / 2);

        // Tomo el fin del centro como la posición siguiente a la del inicio
        *center_end = *center_start + 1;
    }

    // Si n es impar, el centro está en una sola posición, es decir que el inicio y el fin son coincidentes
    else
    {
        // Esta posición se calcula como el siguiente a la división entre la dimensión de la pirámide y 2
        *center_start = *center_end = ((n / 2) + 1);
    }

    // La función no retorna nada porque, al usar punteros, modifica las variables originales que guardan la posición del centro
    return;
}
