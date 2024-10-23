/* ************************************************************
    * CONFIGURACIÓN DEL ARCHIVO *
   ************************************************************ */

/* --------------- LIBRERÍAS UTILIZADAS --------------- */

// Librería estándar de entrada y salida en C
#include <stdio.h>

// Librería para trabajar con booleanos (verdadero y falso)
#include <stdbool.h>

// Librería para usar la función rand()
#include <stdlib.h>

// Librería para usar la función time() como semilla de rand()
#include <time.h>

/* --------------- LLAMADA A HEADERS --------------- */

// Header correspondiente al archivo que recibe y procesa el input del usuario
#include "Front_End/get_input.h"

// Header correspondiente al archivo que imprime la retícula actual
#include "Back_End/print_grid.h"


/* ************************************************************
    * FUNCIÓN PRINCIPAL *
   ************************************************************ */

// La función principal imprime los mensajes en pantalla y llama a las otras funciones
int main(void)
{
    /* --------------- INICIALIZACIÓN DE LA RETÍCULA --------------- */

    // Llamamos a la función srand con la semilla time para generar números "aleatorios"
    srand(time(NULL));

    // Definimos un arrary para la retícula actual y otro para la retícula siguiente
    int current_grid[HEIGHT][WIDTH] = {0};
    int next_grid[HEIGHT][WIDTH] = {0};

    // Definimos dos variables para ubicar a las células en el array correspondiente a la retícula
    int cell_row;
    int cell_col;

    // Definimos una variable para guardar la cantidad aleatoria de células vivas que habrá al inicio
    int alive_cells = (rand() % (HEIGHT * WIDTH));

    /* Inicializamos un contador de células vivas en 0 y lo aumentamos en 1 al iniciar una célula como viva, hasta llegar a la 
    cantidad aleatoria calculada anteriormente */
    for(int alive_cells_count = 0; alive_cells_count < alive_cells; alive_cells_count++)
    {
        // Nos ubicamos en una fila y columna aleatoria
        cell_row = (rand() % HEIGHT);
        cell_col = (rand() % WIDTH );

        // Inicializamos esa posición aleatoria con una célula viva
        current_grid[cell_row][cell_col] = 1;
    }

    // Definimos una variable que guardará el número total de generaciones que quiere ejecutar el usuario
    int total_gens;
    
    // Definimos una variable que contará el número de generaciones que se van ejecutando (desde el input del usuario)
    int current_gen;

    /* --------------- IMPRESIÓN DE LA RETÍCULA --------------- */
    
    // Imprimimos la generación actual hasta que el usuario presione 'q' (o 'Q') para salir o cualquier caracter inválido
    while(((total_gens = read_user_input()) != EXIT_REQUEST) && syntax_error == false)
    {
        /* Inicializamos el contador de generaciones en 0 y lo aumentamos en 1 al terminar de imprimir cada generación,
        hasta imprimir todas las generaciones que indicó el usuario */  
        for(current_gen = 0; current_gen < total_gens; current_gen++)
        {
            // Imprimimos la retícula correspondiente a la generación actual
            print_grid(current_grid);

            // Hacemos dos saltos de línea para separar las generaciones
            printf("\n \n");

            /* --------------- ACTUALIZACIÓN DE LA RETÍCULA --------------- */

            // Calculamos cómo se verá la retícula de la siguiente generación
            next_generation(current_grid, next_grid);

            // Copiamos la retícula de la siguiente generación en la retícula actual
            copy_grid(current_grid, next_grid);
        }
    }

    // La función retorna 0 si todo funciona correctamente
    return 0;
}

