/* *****************************************************************
    *                     FILE CONFIGURATION                      *
   ***************************************************************** */

/* ---------------------- NECESSARY HEADERS ------------------------ */

// Header corresponding to this file
#include "display_grid.h"


/* *****************************************************************
    *                    GRID DISPLAY FUNCTION                    *
   ***************************************************************** */

// Function displays the grid for the current generation using Allegro
void display_grid(ALLEGRO_DISPLAY *display, int grid[HEIGHT][WIDTH])
{
    // Begin display updates
    al_clear_to_color(DEAD_COLOR);

    // Initialize row counter at 0 and increase by 1 after each row, until reaching 'HEIGHT'
    for(int row = 0; row < HEIGHT; row++)
    {
        // Initialize column counter at 0 and increase by 1 after each position in the same row, until reaching 'WIDTH'
        for(int col = 0; col < WIDTH; col++)
        {
            // Calculate x and y coordinates based on cell size
            int x = col * CELL_SIZE;
            int y = row * CELL_SIZE;

            // Draw filled rectangle for each cell
            if(grid[row][col] == 1)
            {
                // Cell is alive; use alive color
                al_draw_filled_rectangle(x, y, x + CELL_SIZE, y + CELL_SIZE, ALIVE_COLOR);
            }

            else
            {
                // Cell is dead; use dead color
                al_draw_filled_rectangle(x, y, x + CELL_SIZE, y + CELL_SIZE, DEAD_COLOR);
            }

            // Draw grid lines around each cell
            al_draw_rectangle(x, y, x + CELL_SIZE, y + CELL_SIZE, GRID_COLOR, 1);
        }
    }

    al_rest(0.5);

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
