/* *****************************************************************
    *                     FILE CONFIGURATION                      *
   ***************************************************************** */

/* --------------------- NECESSARY LIBRARIES --------------------- */

// Standard Input/Output library
#include <stdio.h>

// Boolean library
#include <stdbool.h>

// Random number generation library
#include <stdlib.h>

// Time library for random number generation
#include <time.h>

/* ---------------------- NECESSARY HEADERS ------------------------ */

// Header corresponding to the file that receives and processes user input
#include "Front_End/get_input.h"

// Header corresponding to the file that displays the current grid using Allegro
#include "Back_End/display_grid.h"


/* *****************************************************************
    *                      MAIN FUNCTION                          *
   ***************************************************************** */

// Function displays messages on the screen and calls other functions
int main(void)
{
    /* ------------------- LOCAL VARIABLES ------------------- */

    // Arrays for the current and next grids
    int current_grid[HEIGHT][WIDTH] = {0};
    int next_grid[HEIGHT][WIDTH] = {0};

    // Variables to store the row and column of the cell being analyzed
    int cell_row;
    int cell_col;

    // Random number of alive cells at the start of the game
    int alive_cells = (rand() % (HEIGHT * WIDTH));

    // Total number of generations to be displayed
    int total_gens;

    // Number of the current generation displayed
    int current_gen;

    /* -------------------- INITIALIZATION -------------------- */

    // Seed the random number generator
    srand(time(NULL));

    // Initialize alive cells counter at 0 and increase by 1 after starting each alive cell, until reaching the random amount
    for(int alive_cells_count = 0; alive_cells_count < alive_cells; alive_cells_count++)
    {
        // Generate random row and column for the cell
        cell_row = (rand() % HEIGHT);
        cell_col = (rand() % WIDTH );

        // Initialize the current position with a living cell
        current_grid[cell_row][cell_col] = 1;
    }

    // Initialize Allegro and create a display
    if(!al_init())
    {
        fprintf(stderr, "Failed to initialize Allegro \n");
        return -1;
    }

    ALLEGRO_DISPLAY *display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    if(!display)
    {
        fprintf(stderr, "Failed to create display \n");
        return -1;
    }

    /* ------------------ DISPLAY AND UPDATE ------------------ */
    
    // Display the current generation until the user presses 'q' (or 'Q') to exit or any invalid character
    while(((total_gens = read_user_input()) != EXIT_REQUEST) && syntax_error == false)
    {
        // Initialize generation counter at 0 and increase by 1 after displaying each generation, until reaching the total number of generations
        for(current_gen = 0; current_gen < total_gens; current_gen++)
        {
            // Display the grid corresponding to the current generation using Allegro
            display_grid(display, current_grid);

            // Calculate the next generation based on the current generation
            next_gen(current_grid, next_grid);

            // Copy the grid of the next generation into the current grid
            copy_grid(current_grid, next_grid);
        }
    }

    // Destroy the display after use
    al_destroy_display(display);

    // Function returns 0 if everything works correctly
    return 0;

}
