/* ************************************************************
    * CONFIGURACIÓN DEL HEADER *
   ************************************************************ */

//Nos aseguramos de que el Header solo se incluya una vez 
#ifndef PRINT_GRID
#define PRINT_GRID

/* --------------- LIBRERÍAS UTILIZADAS --------------- */

// Librería estándar de entrada y salida en C
#include <stdio.h>

/* --------------- LLAMADA A HEADERS --------------- */

// Header correspondiente al archivo que calcula la siguiente generación del juego
#include "calc_gen.h"

/* --------------- PROTOTIPOS DE FUNCIONES --------------- */

// La función imprime la retícula correspondiente a la generación actual
void print_grid(int grid[HEIGHT][WIDTH]);

// La función copia la retícula de la generación siguiente en la retícula actual
void copy_grid(int current_grid[HEIGHT][WIDTH], int next_grid[HEIGHT][WIDTH]);

#endif
