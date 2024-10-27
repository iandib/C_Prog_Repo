/* *****************************************************************
    *                    HEADER CONFIGURATION                     *
   ***************************************************************** */

// We make sure the header is only included once
#ifndef DISPLAY_GRID
#define DISPLAY_GRID

/* --------------------- NECESSARY LIBRARIES --------------------- */

// Standard Input/Output library
#include <stdio.h>

// Allegro library for graphics
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

/* ---------------------- NECESSARY HEADERS ------------------------ */

// Header corrisponding to the file that calculates the next generation of the game
#include "../Back_End/calc_gen.h"

/* ---------------------- MACROS & CONSTANTS ---------------------- */

// Set up cell size for display
#define CELL_SIZE 40

// Set up colors for display
#define GRID_COLOR al_map_rgb(200, 200, 200)
#define ALIVE_COLOR al_map_rgb(50, 205, 50)
#define DEAD_COLOR al_map_rgb(0, 0, 0)

// Display dimensions based on the grid size
#define DISPLAY_WIDTH (WIDTH * CELL_SIZE)
#define DISPLAY_HEIGHT (HEIGHT * CELL_SIZE)

/* ------------------ PUBLIC FUNCTIONS PROTOTYPES ------------------ */

// Function displays the grid for the current generation using Allegro
void display_grid(ALLEGRO_DISPLAY *display, int grid[HEIGHT][WIDTH]);

// Function copies the grid for the next generation into the current grid
void copy_grid(int current_grid[HEIGHT][WIDTH], int next_grid[HEIGHT][WIDTH]);

#endif

