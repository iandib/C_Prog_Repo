/* *****************************************************************
    *                    HEADER CONFIGURATION                     *
   ***************************************************************** */

// We make sure the header is only included once 
#ifndef CALC_GEN
#define CALC_GEN

/* --------------------- NECESSARY LIBRARIES --------------------- */

// Standard Input/Output library
#include <stdio.h>

// Boolean library
#include <stdbool.h>

/* ---------------------- MACROS & CONSTANTS ---------------------- */

// Height and width of the game grid
#define HEIGHT 15
#define WIDTH 20

// Check that the grid is not too large
#if ((HEIGHT <= 0) || (WIDTH <= 0))
    #error Invalid dimensions: must be greater than 0

// Check that the grid is not too small
#elif ((HEIGHT > 50) || (WIDTH > 50) || (HEIGHT * WIDTH > 1000))
    #warning Unrecommended dimensions: output will be hard to visualize

#endif

/* ------------------ PUBLIC FUNCTIONS PROTOTYPES ------------------ */

// Function calculates the next generation to be displayed based on the current generation and the game rules
void next_gen(int current_grid[HEIGHT][WIDTH], int next_grid[HEIGHT][WIDTH]);

#endif
