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

// Allegro library for graphics
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

/* ---------------------- NECESSARY HEADERS ------------------------ */

// Header corresponding to the file that displays the current grid using Allegro
#include "Front_End/display_grid.h"


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

    // Number of the current generation displayed
    int current_gen;

    // Set up Allegro display pointer
    ALLEGRO_DISPLAY * display = NULL;

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

    /* ---------------- ALLEGRO INITIALIZATION ---------------- */

    // Attempt to initialize Allegro; if failed, return -1
    if (!al_init())
    {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    // Attempt to initialize Allegro primitives addon; if failed, return -1
    if(!al_init_primitives_addon())
    {
        fprintf(stderr, "Failed to initialize Allegro primitives addon\n");
        return -1;
    }

    // Attempt to create display of 'WIDTH' x 'HEIGHT'; if failed, return -1
    display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT); 
    if (!display)
    {
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }

    // Attempt to install keyboard; if failed, return -1
    if(!al_install_keyboard())
    {
        fprintf(stderr, "Failed to initialize Allegro \n");
        return -1;
    }

    // Create event queue for keyboard events
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    // Variable to store the event
    ALLEGRO_EVENT ev;

        // Variable to store the number pressed by the user
    int numero = 0;


    /* ------------------ DISPLAY AND UPDATE ------------------ */
    while(numero != -1)
    {
    	numero = 0;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            // If the key pressed is a number, convert it to a number 0-9
            if ((ev.keyboard.keycode >= ALLEGRO_KEY_0) && (ev.keyboard.keycode <= ALLEGRO_KEY_9))
            {
                numero = ev.keyboard.keycode - ALLEGRO_KEY_0;
            }

            // If the key pressed is the ENTER key, display the number of generations entered
            if (numero >= 0 && numero <= 9) 
            {
                // Initialize generation counter at 0 and increase by 1 after displaying each generation, until reaching the total number of generations
                for(current_gen = 0; current_gen < numero; current_gen++)
                {
                    // Display the grid corresponding to the current generation using Allegro
                    display_grid(display, current_grid);

                    // Calculate the next generation based on the current generation
                    next_gen(current_grid, next_grid);

                    // Copy the grid of the next generation into the current grid
                    copy_grid(current_grid, next_grid);
                }
            }

            // If the key pressed is the ESC key, exit the program
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                numero = -1;
            }
        }
    }

    // Destroy the display after use
    al_destroy_display(display);

    // Function returns 0 if everything works correctly
    return 0;

}
