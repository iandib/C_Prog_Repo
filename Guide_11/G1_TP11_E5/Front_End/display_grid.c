/* *****************************************************************
    *                     FILE CONFIGURATION                      *
   ***************************************************************** */

/* ---------------------- NECESSARY HEADERS ------------------------ */

// Header corresponding to this file
#include "display_grid.h"

/* ---------------------- ALLEGRO VARIABLES ---------------------- */

// Variables to store the colors for alive, dead, and grid cells
ALLEGRO_COLOR alive_color;
ALLEGRO_COLOR dead_color;
ALLEGRO_COLOR grid_color;


/* *****************************************************************
    *                    GRID DISPLAY FUNCTION                    *
   ***************************************************************** */

// Function displays the grid for the current generation using Allegro
void display_grid(ALLEGRO_DISPLAY *display, int grid[HEIGHT][WIDTH])
{
    /* ------------------- LOCAL VARIABLES ------------------- */
    
    // Variables to store the x and y coordinates of the cell
    int x_coord;
    int y_coord;

    /* -------------------- INITIALIZATION -------------------- */

    // Set colors for alive and dead cells
    alive_color = al_map_rgb(50, 205, 50);
    dead_color = al_map_rgb(0, 0, 0);
    grid_color = al_map_rgb(200, 200, 200);

    // Begin display updates
    al_clear_to_color(dead_color);

    // Initialize row counter at 0 and increase by 1 after each row, until reaching 'HEIGHT'
    for(int row = 0; row < HEIGHT; row++)
    {
        // Initialize column counter at 0 and increase by 1 after each position in the same row, until reaching 'WIDTH'
        for(int col = 0; col < WIDTH; col++)
        {
            // Calculate x and y coordinates based on cell size
            x_coord = col * CELL_SIZE;
            y_coord = row * CELL_SIZE;

            

            // Draw filled rectangle for each cell
            if(grid[row][col] == 1)
            {
                // Cell is alive; use alive color
                al_draw_filled_rectangle(x_coord, y_coord, x_coord + CELL_SIZE, y_coord + CELL_SIZE, alive_color);
            }

            else
            {
                // Cell is dead; use dead color
                al_draw_filled_rectangle(x_coord, y_coord, x_coord + CELL_SIZE, y_coord + CELL_SIZE, dead_color);
            }

            // Draw grid lines around each cell
            al_draw_rectangle(x_coord, y_coord, x_coord + CELL_SIZE, y_coord + CELL_SIZE, grid_color, 1);
        }
    }

    // Refresh display to show updated grid
    al_flip_display();
    
    // Function does not return a value
    return;
}


/* *****************************************************************
    *                     GRID COPY FUNCTION                      *
   ***************************************************************** */

// Function copies the grid for the next generation into the current grid
void copy_grid(int current_grid[HEIGHT][WIDTH], int next_grid[HEIGHT][WIDTH])
{
    // Initialize row counter at 0 and increase by 1 after each row, until reaching 'HEIGHT - 1'
    for(int row = 0; row < HEIGHT; row++)
    {
        // Initialize column counter at 0 and increase by 1 after each position in the same row, until reaching 'WIDTH - 1'
        for(int col = 0; col < WIDTH; col++)
        {
            /* Copy each position of the grid corresponding to the next generation into the same position in the grid 
            corresponding to the current generation */
            current_grid[row][col] = next_grid[row][col];
        }
    }

    // Function does not return a value
    return;
}
