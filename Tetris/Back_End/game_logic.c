/* *****************************************************************
    *                        INFORMATION                          *
   ***************************************************************** 
   
    * @file game_logic.c
    * @brief Game logic functions for the Tetris game
    * @date 25-11-2024
    * @authors Luchelli, Caorsi
    * @contributors Moschini, Dib
    
    This file contains the core functions for handling the Tetris 
    game logic, including the management of the game grid, 
    tetromino movements, row clearing, scoring, and game state.

*/


/* *****************************************************************
    *                     FILE CONFIGURATION                      *
   ***************************************************************** */

/* --------------------- NECESSARY LIBRARIES --------------------- */

// Standard I/O library for debugging
#include <stdio.h>

// Standard boolean data types library
#include <stdbool.h>

// Standard time library, used as the seed of the random number generator
#include <time.h>

// Standard utilities library, used to generate random numbers
#include <stdlib.h>

// Standard semaphore (threads) management library
#include <semaphore.h>

/* ---------------------- NECESSARY HEADERS ------------------------ */

// Header containing game logic function prototypes
#include "game_logic.h"

// Header containing display and sound function prototypes
#include "../th2_display_sound.h"

/* ---------------------- GLOBAL VARIABLES ---------------------- */

// Array of tetromino shapes
extern int tetrominoShapes[NUM_SHAPES][TETROMINO_R][TETROMINO_H][TETROMINO_W];

// Semaphore used for thread synchronization
extern sem_t s;

/* ----------------- PRIVATE FUNCTIONS PROTOTYPES ----------------- */

// Copies tetromino shape onto either active or next tetromino, depending on the bool active
static void copyShape(const int source[TETROMINO_H][TETROMINO_W], Game* game, bool active);

// Rotates the active tetromino if possible
static void rotate(Game* game);

// Fixes active tetromino in its current position, filling the game grid with its shape
static void fixTetromino(Game* game);

// Clears completed rows from the game grid and updates score and level
static void clearRows(Game* game);

// Checks if the current tetromino can move sideways in the specified direction
static bool canMoveSideways(Game* game, int xOffset);

// Checks if the current tetromino can move down
static bool canMoveDown(const Game* game);

// Checks if the game is over by detecting collisions of the active tetromino with the grid
static bool isGameOver(const Game* game);

// Updates the game score based on the number of rows cleared and the current level
static void updateScore(Game* game, int numClearedRows);

// Updates the color map of the grid to match the fixed tetromino
static void updateColorMap(Game* game, int row, int col);

// Updates the game level based on the total number of cleared lines
static void updateLevel(Game* game);


/* *****************************************************************
    *                       MAIN GAME LOGIC                       *
   ***************************************************************** */

/* Contains the main game logic executed by thread 1.
    @param gamep Pointer to the Game structure containing the game state. */
void* th1_gamelogic(void* gamep)
{
	/* ------------------- LOCAL VARIABLES ------------------- */
    
    // Pointer to the game state
    Game* game = gamep;

    // File pointer to check for a saved game
    FILE* save = fopen("saving.txt", "r");
	
    /* ------------------- INITIALIZATION ------------------- */
    
    // Seed the random number generator with the current time
    srand(time(NULL));

    // Initialize the game
	initializeGame(game);
    
    // Check if a saved game file exists
    if (save != NULL)
    {
        // Close the file after confirming its existence
    	fclose(save);

        // Set the pause flag to display the pause screen
		game->pause = true;

        // Restore the saved game state from the file
        #ifdef PC
		recover_game(game);
        #endif
	}

    else
	{
    	// Set the game menu to the "play" state
    	game->menu = PLAY;
	}

    /* --------------------- GAME LOOP --------------------- */
    
    // Continue running the game loop until the quit flag is set
	while(!game->quit)
	{
		// Check if the game is in progress (not in menu, pause, or game over states)
        if(!game->menu && !game->pause && !game->gameOver && !game->restart)
		{
            // Handle downward movement of the active tetromino
            if(game->activeTetromino.move_down)
			{
				// Move the tetromino down if the movement is valid
                if(canMoveDown(game))									
				{
					game->activeTetromino.y++;
					game->activeTetromino.move_down--;
					playSoundIndex(MOVE_SIDEWAYS);
				}

                else													
				{
					// Stop downward movement if the tetromino reaches the surface
					game->activeTetromino.move_down = 0;

					// Fix the tetromino in its current position
                    fixTetromino(game);

					// Clear completed rows from the game grid
                    clearRows(game);

					// Generate a new tetromino for the next turn
                    generateNewTetromino(game);
				}
			}

			// Handle leftward movement of the active tetromino
            else if (game->activeTetromino.move_left)
			{
				// Move the tetromino left if the movement is valid
				if (canMoveSideways(game, -1))
				{
					game->activeTetromino.x--;
					game->activeTetromino.move_left--;
					playSoundIndex(MOVE_SIDEWAYS);
				}

				else
				{
                    // Reset the left movement buffer if movement is invalid
					game->activeTetromino.move_left = 0;
				}
			}

			// Handle rightward movement of the active tetromino
            else if (game->activeTetromino.move_right)
			{
				// Move the tetromino right if the movement is valid
				if (canMoveSideways(game, 1))
				{
					game->activeTetromino.x++;
					game->activeTetromino.move_right--;
					playSoundIndex(MOVE_SIDEWAYS);
				}

				else
				{
                    // Reset the right movement buffer if movement is invalid
					game->activeTetromino.move_right = 0;
				}
			}

			// Handle rotation of the active tetromino
            else if (game->activeTetromino.rotate_)
			{
				// Rotate the tetromino if the rotation is valid
                rotate(game);
			}

		    // Check if the game over condition has been reached
            if (isGameOver(game))
		    {
		        // Set the game over flag and play the corresponding sound
		        game->gameOver = true;
	            playSoundIndex(GAME_OVER);
		    }
		}

        // Handle other game states (menu, pause, or restart)
        else
		{
			// Wait for a signal to proceed (e.g., from another thread)
			sem_wait(&s);
            
            // Reinitialize the game if the restart flag is set
			if (game->restart)
			{
				initializeGame(game);

				// Remove any saved game file
				remove("saving.txt");
			}
		}
	}
	
    // Exit the thread once the quit flag is set
    pthread_exit(0);
}


/* *****************************************************************
    *                       INITIALIZE GAME                       *
   ***************************************************************** */

/* Initializes the game state with default values.
    @param game Pointer to the Game structure to be initialized. */
void initializeGame(Game* game)
{
    /* -------------------- INITIALIZATION -------------------- */

    // Set default game state variables
    game->menu = PLAY;
    game->gameOver = false;
    game->score = 0;
    game->highScoreIndex = 0;
    game->level = 0;
    game->hasLevelChanged = false;
    game->lines = 0;
    game->levelCheckpoint = 1;
    game->fixDelay = 0;
    game->waitingForExit = false;
    game->quit = false;
    game->pause = false;
    game->redraw = true;
    game->restart = false;


    /* ------------------ GAME GRID RESET ------------------ */

    // Clear the game grid and tetromino grid
    for (int i = 0; i < GRID_HEIGHT; i++)
    {
        for (int j = 0; j < GRID_WIDTH; j++)
        {
            game->grid[i][j] = 0;
            game->tetrominoGrid[i][j] = 0;
        }
    }
    /* ------------------ GAME SHAPE STATISTICS RESET ------------------ */
	for (int i = 0; i < NUM_SHAPES; i++)
	{
		game->statistics[i] = 0;
	}


    /* ------------------ TETROMINO SETUP ------------------ */

    // Generate a new random tetromino at the start of the game
    generateNewTetromino(game);
}


/* *****************************************************************
    *                  GENERATE A NEW TETROMINO                   *
   ***************************************************************** */

/* Generates a new random tetromino and updates game statistics.
    @param game Pointer to the Game structure containing the current game state. */
void generateNewTetromino(Game* game)
{
    /* ------------------- LOCAL VARIABLES ------------------- */

    // Randomly selected index for the next tetromino shape.
    int shapeIndex = rand() % NUM_SHAPES;

    // Tracks whether this is the first tetromino generated in the game.
    static bool first_tetromino = true;

    /* --------------------- GAME LOGIC --------------------- */

    // If this is not the first tetromino:
    if (!first_tetromino) 
    {
        // Update the active tetromino with the values from the "next" tetromino.
        if (game->nextTetromino.shapeIndex == I) 
        {
            // Adjust the initial position for "I" tetromino.
            game->activeTetromino.x = game->nextTetromino.x - 1;
            game->activeTetromino.y = game->nextTetromino.y - 1;
        }

        else 
        {
            game->activeTetromino.x = game->nextTetromino.x;
            game->activeTetromino.y = game->nextTetromino.y;
        }

        // Copy the "next" tetromino shape and attributes to the active tetromino.
        copyShape(game->nextTetromino.shape, game, true);
        game->activeTetromino.shapeIndex = game->nextTetromino.shapeIndex;
        game->activeTetromino.rotation = game->nextTetromino.rotation;
        game->activeTetromino.move_down = game->nextTetromino.move_down;
        game->activeTetromino.move_left = game->nextTetromino.move_left;
        game->activeTetromino.move_right = game->nextTetromino.move_right;
        game->activeTetromino.rotate_ = game->nextTetromino.rotate_;

        // Increment the shape statistics for the "next" tetromino.
        game->statistics[game->nextTetromino.shapeIndex]++;

        // Generate a new "next" tetromino.
        game->nextTetromino.x = GRID_WIDTH / 2 - 1;
        game->nextTetromino.y = 0;
        copyShape(tetrominoShapes[shapeIndex][0], game, false);
        game->nextTetromino.shapeIndex = shapeIndex;
    }

    else 
    {
        // If this is the first tetromino, initialize both "active" and "next".
        first_tetromino = false;

        // Set the "next" tetromino.
        game->nextTetromino.x = GRID_WIDTH / 2 - 1;
        game->nextTetromino.y = 0;
        copyShape(tetrominoShapes[shapeIndex][0], game, false);
        game->nextTetromino.shapeIndex = shapeIndex;

        // Generate the first "active" tetromino.
        shapeIndex = rand() % NUM_SHAPES;

        // Adjust the position for the "I" tetromino.
        if (shapeIndex == I) 
        {
            game->activeTetromino.x = GRID_WIDTH / 2 - 2;
            game->activeTetromino.y = -1;
        }

        else 
        {
            game->activeTetromino.x = GRID_WIDTH / 2 - 1;
            game->activeTetromino.y = 0;
        }

        // Set the attributes for the active tetromino.
        copyShape(tetrominoShapes[shapeIndex][0], game, true);
        game->activeTetromino.move_down = 0;
        game->activeTetromino.rotate_ = 0;
        game->activeTetromino.shapeIndex = shapeIndex;

        // Update statistics for the generated shape.
        game->statistics[shapeIndex]++;
    }

    /* ----------------------- RESET ----------------------- */

    // Reset attributes for the "next" tetromino.
    game->nextTetromino.rotation = 0;
    game->nextTetromino.move_down = 0;
    game->nextTetromino.move_left = 0;
    game->nextTetromino.move_right = 0;
    game->nextTetromino.rotate_ = 0;
}


/* *****************************************************************
    *                          SHAPE COPY                         *
   ***************************************************************** */

/* Copies tetromino shape onto either active or next tetromino, depending on the bool active.
    @param source 2D array representing the tetromino shape.
    @param game Pointer to the Game structure.
    @param active Boolean flag indicating whether to copy to the active tetromino or the next one. */
static void copyShape(const int source[TETROMINO_H][TETROMINO_W], Game* game, bool active)
{
    /* -------------------- LOCAL VARIABLES -------------------- */

    // Loop counters for rows and columns
    int i, j;

    /* ------------------ COPY TO TARGET SHAPE ------------------ */

    if (active)
    {
        // Copy shape into the active tetromino
        for (i = 0; i < TETROMINO_H; i++)
        {
            for (j = 0; j < TETROMINO_W; j++)
            {
                game->activeTetromino.shape[i][j] = source[i][j];
            }
        }
    }

    else
    {
        // Copy shape into the next tetromino
        for (i = 0; i < TETROMINO_H; i++)
        {
            for (j = 0; j < TETROMINO_W; j++)
            {
                game->nextTetromino.shape[i][j] = source[i][j];
            }
        }
    }
}


/* *****************************************************************
    *                       ROTATE TETROMINO                      *
   ***************************************************************** */

/* Rotates the active tetromino if possible.
    @param game Pointer to the Game structure. */
static void rotate(Game* game)
{
    /* -------------------- LOCAL VARIABLES -------------------- */

    // Store current and new rotation states
    int oldRotation = game->activeTetromino.rotation;
    int newRotation = (oldRotation + 1) % 4;

    // Rotation validity flag
    bool canRotate = true;

    // Loop counters for rows and columns
    int i, j;

    /* ---------------------- VALIDATION ---------------------- */

    for (i = 0; i < TETROMINO_H; i++)
    {
        for (j = 0; j < TETROMINO_W; j++)
        {
            if (tetrominoShapes[game->activeTetromino.shapeIndex][newRotation][i][j] != 0)
            {
                // Calculate new position
                int row = game->activeTetromino.y + i;
                int col = game->activeTetromino.x + j;

                // Check bounds and collisions
                if (col < 0 || col >= GRID_WIDTH || row < 0 || row >= GRID_HEIGHT ||
                    (row >= 0 && game->grid[row][col] != 0))
                {
                    canRotate = false;
                    j = TETROMINO_W; // Break inner loop
                    i = TETROMINO_H; // Break outer loop
                }
            }
        }
    }

    /* ------------------- APPLY ROTATION ------------------- */

    if (canRotate)
    {
        game->activeTetromino.rotation = newRotation;

        for (i = 0; i < TETROMINO_H; i++)
        {
            for (j = 0; j < TETROMINO_W; j++)
            {
                // Update shape to new rotation
                game->activeTetromino.shape[i][j] =
                    tetrominoShapes[game->activeTetromino.shapeIndex][newRotation][i][j];
            }
        }

        // Update rotation buffer
        game->activeTetromino.rotate_--;

        // Play rotation sound
        playSoundIndex(ROTATE);
    }

    else
    {
        // Clear rotation buffer if rotation is invalid
        game->activeTetromino.rotate_ = 0;
    }
}


/* *****************************************************************
    *                    FIX TETROMINO IN GRID                    *
   ***************************************************************** */

/* // Fixes active tetromino in its current position, filling the game grid with its shape.
    @param game Pointer to the Game structure. */
static void fixTetromino(Game* game)
{
    /* -------------------- LOCAL VARIABLES -------------------- */

    // Loop counters for rows and columns
    int i, j;

    // Grid position variables
    int row, col;

    /* ---------------------- UPDATE GRID ---------------------- */

    for (i = 0; i < TETROMINO_H; i++)
    {
        for (j = 0; j < TETROMINO_W; j++)
        {
            if (game->activeTetromino.shape[i][j] != 0)
            {
                // Calculate grid position
                row = game->activeTetromino.y + i;
                col = game->activeTetromino.x + j;

                // Mark grid cell as occupied
                game->grid[row][col] = 1;

                // Update color map for the grid cell
                updateColorMap(game, row, col);
            }
        }
    }

    // Play sound effect for fixing the tetromino
    playSoundIndex(FIX);
}


/* *****************************************************************
    *                          CLEAR ROWS                         *
   ***************************************************************** */

/* Clears completed rows from the game grid and updates score and level.
    @param game Pointer to the Game structure. */
static void clearRows(Game* game)
{
    /* -------------------- LOCAL VARIABLES -------------------- */

    // Indices for loops
    int i, j, k;

    // Counter for the number of rows cleared
    int numClearedRows = 0;

    /* --------------------- ROW CHECKING --------------------- */

    // Iterate through the grid from the bottom to the top
    for (i = GRID_HEIGHT - 1; i >= 0; i--)
    {
        // Flag to check if the current row is full
        bool isRowFull = true;

        // Check if the current row is completely filled
        for (j = 0; j < GRID_WIDTH; j++)
        {
            if (game->grid[i][j] == 0)
            {
                isRowFull = false;
                break;
            }
        }

        /* ----------------- ROW CLEARING ----------------- */

        // If the row is full, clear it and shift rows down
        if (isRowFull)
        {
            // Shift all rows above the current row down by one
            for (k = i; k > 0; k--)
            {
                for (j = 0; j < GRID_WIDTH; j++)
                {
                    game->grid[k][j] = game->grid[k - 1][j];
                }
            }

            // Clear the topmost row
            for (j = 0; j < GRID_WIDTH; j++)
            {
                game->grid[0][j] = 0;
            }

            // Increment the count of cleared rows
            numClearedRows++;

            // Restart the current row check to account for the shifted rows
            i++;
        }
    }

    /* ----------------- SCORE & LEVEL UPDATE ----------------- */

    // Update the game score based on the number of cleared rows
    updateScore(game, numClearedRows);

    // Update the total lines cleared in the game
    game->lines += numClearedRows;

    // Update the game level if necessary
    updateLevel(game);
}


/* *****************************************************************
    *                     HORIZONTAL MOVEMENT                     *
   ***************************************************************** */

/* Checks if the current tetromino can move sideways in the specified direction.
    @param game Pointer to the Game structure.
    @param xOffset Horizontal offset to check (-1 for left, 1 for right).
    @return true if the tetromino can move sideways, false otherwise. */
static bool canMoveSideways(Game* game, int xOffset)
{
    /* ------------------- LOCAL VARIABLES ------------------- */

    // New x-coordinate for the tetromino
    int newX = game->activeTetromino.x + xOffset;

    // Flag to determine if the move is possible
    bool canMove = true;

    // Loop indices
    int i, j;

    // Row and column of the tetromino in the game grid
    int col, row;

    /* --------------------- VALIDATION --------------------- */

    // Check each block of the tetromino's shape
    for (i = TETROMINO_H - 1; i >= 0; i--)
    {
        for (j = 0; j < TETROMINO_W; j++)
        {
            // Skip empty cells in the tetromino's shape
            if (game->activeTetromino.shape[i][j] != 0)
            {
                // Calculate the new row and column in the grid
                row = game->activeTetromino.y + i;
                col = newX + j;

                // Check if the position is out of bounds or collides with existing blocks
                if (col < 0 || col >= GRID_WIDTH || 
                    row >= GRID_HEIGHT || 
                    (row >= 0 && game->grid[row][col] != 0))
                {
                    canMove = false;
                    break;
                }
            }
        }

        // Exit the loop if a collision or invalid move is detected
        if (!canMove)
        {
            break;
        }
    }

    // Return whether the tetromino can move sideways
    return canMove;
}


/* *****************************************************************
    *                        DOWN MOVEMENT                        *
   ***************************************************************** */

/* Checks if the current tetromino can move down.
    @param game Pointer to the Game structure containing the current game state.
    @return true if the tetromino can move down, false otherwise. */
static bool canMoveDown(const Game* game)
{
    /* ------------------- LOCAL VARIABLES ------------------- */

    // Row and column positions of the active tetromino blocks.
    int row, col;

    /* --------------------- VALIDATION --------------------- */

    // Iterate through each block of the active tetromino.
    for (int i = 0; i < TETROMINO_H; i++) 
    {
        for (int j = 0; j < TETROMINO_W; j++) 
        {
            // Check if the block is part of the tetromino.
            if (game->activeTetromino.shape[i][j] != 0) 
            {
                // Calculate the new position of the block after moving down.
                row = game->activeTetromino.y + i + 1;
                col = game->activeTetromino.x + j;

                // If the block is out of bounds or collides with another block:
                if (row >= GRID_HEIGHT || game->grid[row][col] != 0) 
                {
                    return false;
                }
            }
        }
    }

    // If all blocks can move down, return true.
    return true;
}



/* *****************************************************************
    *                       CHECK GAME OVER                       *
   ***************************************************************** */

/* Checks if the game is over by detecting collisions of the active tetromino with the grid.
    @param game Pointer to the Game structure.
    @return true if the game is over, false otherwise. */
static bool isGameOver(const Game* game)
{
    /* ------------------- LOCAL VARIABLES ------------------- */

    // Indices for loops
    int i, j;

    // Row and column coordinates of the tetromino in the grid
    int row, col;

    /* ------------------ COLLISION CHECK ------------------ */

    // Iterate through the tetromino's shape matrix
    for (i = 0; i < TETROMINO_H; i++)
    {
        for (j = 0; j < TETROMINO_W; j++)
        {
            // Check if the cell contains part of the tetromino
            if (game->activeTetromino.shape[i][j] != 0)
            {
                // Calculate the cell's position in the grid
                row = game->activeTetromino.y + i;
                col = game->activeTetromino.x + j;

                // If the position collides with the grid, the game is over
                if (game->grid[row][col] != 0)
                {
                    return true;
                }
            }
        }
    }

    // No collisions detected, the game continues
    return false;
}


/* *****************************************************************
    *                         UPDATE SCORE                        *
   ***************************************************************** */

/* Updates the game score based on the number of rows cleared and the current level.
    @param game Pointer to the Game structure.
    @param numClearedRows Number of rows cleared in the current move. */
static void updateScore(Game* game, int numClearedRows)
{
    /* ------------------ SCORE CALCULATION ------------------ */

    // Update the score based on the number of rows cleared
    switch (numClearedRows)
    {
        case 1:
            game->score += 40 * (game->level + 1);
            playSoundIndex(BURN); // Play sound for single row clearance
            break;

        case 2:
            game->score += 100 * (game->level + 1);
            playSoundIndex(BURN); // Play sound for two rows cleared
            break;

        case 3:
            game->score += 300 * (game->level + 1);
            playSoundIndex(BURN); // Play sound for three rows cleared
            break;

        case 4:
            game->score += 1200 * (game->level + 1);
            playSoundIndex(TETRIS); // Play "TETRIS" sound for four rows cleared
            break;

        default:
            break;
    }
}


/* *****************************************************************
    *                      UPDATE COLOR MAP                       *
   ***************************************************************** */

/* Updates the color map of the grid to match the fixed tetromino.
    @param game Pointer to the Game structure.
    @param row Row index of the grid.
    @param col Column index of the grid. */
static void updateColorMap(Game* game, int row, int col)
{
    // This function is only used for the PC version of the game
    #ifdef PC

    /* ------------------- COLOR ASSIGNMENT ------------------- */

    // Assign color based on the tetromino shape index
    switch (game->activeTetromino.shapeIndex)
    {
        case I:
        case O:
        case T:
            // Assign white color based on level
            game->tetrominoGrid[row][col] = BLOCK_TYPES * (game->level % LEVEL_STYLES) + WHITE;
            break;

        case L:
        case Z:
            // Assign light color based on level
            game->tetrominoGrid[row][col] = BLOCK_TYPES * (game->level % LEVEL_STYLES) + LIGHT;
            break;

        case J:
        case S:
            // Assign dark color based on level
            game->tetrominoGrid[row][col] = BLOCK_TYPES * (game->level % LEVEL_STYLES) + DARK;
            break;
    }

    #endif // PC
}


/* *****************************************************************
    *                      UPDATE GAME LEVEL                       *
   ***************************************************************** */

/* Updates the game level based on the total number of cleared lines.
    @param game Pointer to the Game structure containing the current game state. */
static void updateLevel(Game* game)
{
    /* --------------------- LEVEL CHECK --------------------- */

    // If the total cleared lines reach or exceed the checkpoint for the current level:
    if (game->lines >= game->levelCheckpoint) 
    {
        // Increment the game level.
        game->level++;

        // Update the checkpoint to the next threshold.
        game->levelCheckpoint += 10;

        // Set the flag indicating that the level has changed.
        game->hasLevelChanged = true;
    }
}
