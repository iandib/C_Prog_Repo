/* ************************************************************
    * CONFIGURACIÓN DEL HEADER *
   ************************************************************ */

//Nos aseguramos de que el Header solo se incluya una vez 
#ifndef CALC_GEN
#define CALC_GEN

/* --------------- DIMENSIONES DEL JUEGO --------------- */

// Definimos el alto y ancho de la retícula del juego
#define HEIGHT 15
#define WIDTH 20

// Revisamos que la retícula se pueda imprimir
#if ((HEIGHT <= 0) || (WIDTH <= 0))
    #error Invalid dimensions: must be greater than 0

// Revisamos que la retícula no se vea demasiado chica
#elif ((HEIGHT > 50) || (WIDTH > 50) || (HEIGHT * WIDTH > 1000))
    #warning Unrecommended dimensions: output will be hard to visualize

#endif

/* --------------- PROTOTIPOS DE FUNCIONES --------------- */

// La función calcula la siguiente generación que debe imprimirse a partir de la generación actual y de las reglas del juego
void next_generation(int current_grid[HEIGHT][WIDTH], int next_grid[HEIGHT][WIDTH]);

#endif
