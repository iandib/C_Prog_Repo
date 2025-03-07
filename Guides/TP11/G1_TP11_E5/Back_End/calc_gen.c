/* *****************************************************************
    *                     FILE CONFIGURATION                      *
   ***************************************************************** */

/* ---------------------- NECESSARY HEADERS ------------------------ */

// Header corresponding to the current file
#include "calc_gen.h"

/* ----------------- PRIVATE FUNCTIONS PROTOTYPES ----------------- */

// Function counts how many alive neighbors the cell at (row, col) in the current generation has
static int count_alive_neib(int grid[HEIGHT][WIDTH], int row, int col);


/* *****************************************************************
    *                  NEXT GENERATION FUNCTION                   *
   ***************************************************************** */

// Function calculates the next generation to be displayed based on the current generation and the game rules
void next_gen(int current_grid[HEIGHT][WIDTH], int next_grid[HEIGHT][WIDTH])
{
    // Initialize row counter at 0 and increase by 1 after each row, until reaching 'HEIGHT - 1'
    for(int row = 0; row < HEIGHT; row++)
    {
        // Initialize column counter at 0 and increase by 1 after each position in the same row, until reaching 'WIDTH - 1'
        for(int col = 0; col < WIDTH; col++)
        {
            // Count how many alive neighbors the cell at (row, col) has
            int alive_neib = count_alive_neib(current_grid, row, col);

            // If the cell at (row, col) is alive
            if(current_grid[row][col] == 1)
            {
                // Determines if the cell dies or survives based on the number of alive neighbors
                next_grid[row][col] = (alive_neib < 2 || alive_neib > 3) ? 0 : 1;
            }

            // If the position (row, col) is empty
            else
            {
                // If it has exactly 3 neighbors, a cell is born; otherwise, it remains empty
                next_grid[row][col] = (alive_neib == 3) ? 1 : 0;
            }
        }
    }

    // Function does not return a value
    return;
}


/* *****************************************************************
    *                    ALIVE CELLS FUNCTION                     *
   ***************************************************************** */

// Function counts how many alive neighbors the cell at (row, col) in the current grid has
static int count_alive_neib(int grid[HEIGHT][WIDTH], int row, int col)
{
    /* ------------------- LOCAL VARIABLES ------------------- */

    // Number of alive neighbors
    int alive_neib = 0;

    // Row displacement from the position (row, col)
    int row_dispm;

    // Column displacement from the position (row, col)
    int col_dispm;

    // Flag to check if the neighboring cell is within the grid boundaries
    bool in_bounds = false;

    /* ----------------------- UPDATE ----------------------- */

    // Iterate through the three columns from 1 place to the left of (row, col) to 1 place to its right
    for(row_dispm = -1; row_dispm <= 1; row_dispm++)
    {
        // Reset in_bounds to false at the beginning of each row_dispm iteration
        in_bounds = false;

        // Repeat for the three rows from 1 place below (row, col) to 1 place above it
        for(col_dispm = -1; col_dispm <= 1; col_dispm++)
        {
            // If we are at the the cell itself, skip it
            if(row_dispm == 0 && col_dispm == 0)
            {
                continue;
            }

            // Calculate the coordinates of each neighboring cell (updated with each value of x and y in the 3x3 loop)
            int neigb_row = row + row_dispm;
            int neigb_col = col + col_dispm;

            // If the neighboring cell is within the grid boundaries, set the flag to true
            if((neigb_row >= 0) && (neigb_row < HEIGHT) && (neigb_col >= 0) && (neigb_col < WIDTH))
            {
                in_bounds = true;
            }

            // If the neighboring cell is within bounds and is alive, increase the counter of alive neighbors
            if(in_bounds && grid[neigb_row][neigb_col] == 1)
            {
                alive_neib++;
            }
        }
    }

    // Function returns the total number of alive neighbors
    return alive_neib;
}
