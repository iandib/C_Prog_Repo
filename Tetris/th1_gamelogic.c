/*
 * th1_gamelogic.c
 *
 *  Created on: Nov 25, 2024
 *      Author: juani
 */
#include <stdbool.h>	
#include <stdio.h>
#include "common.h"
#include "th1_gamelogic.h"
#include "th2_display_sound.h"
#include <time.h>
#include <stdlib.h>
#include <semaphore.h>
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define BLOCK_TYPES 4
#define LEVEL_STYLES 10


 /*******************************************************************************
  * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
  ******************************************************************************/

  // Enums
enum blockTypes
{
    WHITE = 0,
    LIGHT,
    DARK,
    STRIPES
};

static void copyShape(const int source[TETROMINO_H][TETROMINO_W], Game* game, bool active);
static void rotate(Game* game);														//Checks if the tetromino can rotate, if it is possible, it is rotated.
static bool canMoveSideways(Game* game, int xOffset);								//Checks if the current tetromino can move sideways
static bool canMoveDown(const Game* game);											//Checks if the current tetromino can move down
static bool isGameOver(const Game* game);											//Checks for game over
static void updateScore(Game* game, int numClearedRows);							//Updates the current game score
static void clearRows(Game* game);													//Clears full rows
static void fixTetromino(Game* game);												//Fixes current tetromino in its current position (fills game grid with its shape)
static void updateColorMap(Game* game, int row, int col);							//Updates of the fixed tetromino (makes it possible for the grid to have different colors)
static void updateLevel(Game* game);												//Updates game level

extern int tetrominoShapes[NUM_SHAPES][TETROMINO_R][TETROMINO_H][TETROMINO_W];		//Array of tetromino shapes
extern sem_t s;

void * th1_gamelogic(void* gamep)
{
	Game* game = gamep;													//First, the game struct and leaderboard [TO BE CHECKED] are initialized.
	initializeGame(game);
	initialize_leaderboard(game);
    FILE* save = fopen("saving.txt", "r");								//If we happen to find an old game, it is restored and pause screen is automatically activated, and if we do not, we will find the menu as soon as we enter the game.
    if(save != NULL){
    	fclose(save);
		game->pause = true;
		recover_game(game);
	}
    else
	{
    	game->menu = true;
	}
	srand(time(NULL));													//rand() seed is properly set for a future run
	while(!game->quit)
	{
		if(!game->menu && !game->pause && !game->gameOver && !game->restart)				//We essentially have 4 states, menu, pause, game over and game. The program runs what is inside this conditional when it is in game. Whereas, the th1 waits for a signal from the semaphore which would be set soon in th2
		{
			if(game->activeTetromino.move_down)							//If the tetromino was moved down, whether it was caused by the fall-timer od by user clicking, the program will check if that is a valid action
			{
				if(canMoveDown(game))									//If it is, the tetromino is moved down
				{
					game->activeTetromino.y++;
					game->activeTetromino.move_down--;
				}
				else													//If not, that is because we have reached a surface and the program gets ready to fix the tetromino
				{
					game->activeTetromino.move_down = 0;

					fixTetromino(game);									// Fixes the tetromino in its current position on the game grid

					clearRows(game);									// Checks for completed rows and clear them

					generateNewTetromino(game);							// Generates a new random tetromino shape and position
				}
			}
			else if(game->activeTetromino.move_left)					//This conditional checks if the tetromino was moved left. If that is a valid action then it is moved, if not, the buffer is cleared.
			{
				if (canMoveSideways(game, -1))
				{
					game->activeTetromino.x--;
					game->activeTetromino.move_left--;
					playSoundIndex(MOVE_SIDEWAYS);
				}
				else
				{
					game->activeTetromino.move_left = 0;				//Clears the buffer for left-movements
				}
			}
			else if(game->activeTetromino.move_right)					//This conditional checks if the tetromino was moved right. If that is a valid action then it is moved, if not, the buffer is cleared.
			{
				if (canMoveSideways(game, 1))
				{
					game->activeTetromino.x++;
					game->activeTetromino.move_right--;
					playSoundIndex(MOVE_SIDEWAYS);
				}
				else
				{
					game->activeTetromino.move_right = 0;				//Clears the buffer for right-movements
				}
			}
			else if(game->activeTetromino.rotate_)						//This conditional checks if the tetromimo was rotated
			{
				rotate(game);											//Depending on the position of the tetromino, this funtion will check if it is possible to rotate or not the tetromino, if it is, the tetromino will be rotated
			}
		    if (game->lines >= game->levelCheckpoint)					//Depending on the cleared rows so far, the game level is incremented as well as the amount of cleared rows necessary for the next level
		    {
		        game->level++;
		        game->levelCheckpoint += 10;
		    }
		    if (isGameOver(game))										//If game over is reached, the flag that incates so is activated
		    {
		        game->gameOver = true;
	            playSoundIndex(GAME_OVER);
		    }
			game->redraw = true;										//Now we are ready to redraw our grid and HUD
			game->frames++;												//[TO BE CHECKED]
		}
		else															//As soon as we run the program, this conditional is reached. Generating a new tetromino will be necessary, unless we have an old game loaded. If we do, we previously said that the program would go directly to the pause screen
		{
			if(game->menu || game->gameOver)
			{
				//generateNewTetromino(game);
			}
			sem_wait(&s);												//The program waits here for the user to start the game
			if(game->restart)
			{
				initializeGame(game);

				remove("saving.txt");
			}
		}
	}
	pthread_exit(0);													//Finally, if the quit flag is activated, this process is killed
}

void initializeGame(Game* game)											//Sets initial values
{
	game->menu = true;
	game->gameOver = false;
	game->frames = 0;
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

	initialize_leaderboard(game);										//[TO BE CHECKED]

	for (int i = 0; i < GRID_HEIGHT; i++)								//Clears the game grid
	{
		for (int j = 0; j < GRID_WIDTH; j++)
		{
			game->grid[i][j] = 0;
			game->tetrominoGrid[i][j] = 0;
		}
	}
	generateNewTetromino(game);
}

static bool canMoveSideways(Game* game, int xOffset)						// Checks if the tetromino can move horizontally in the specified direction, returning true if it can, and false if it cannot
{
    int newX = game->activeTetromino.x + xOffset;    						// Calculate the new x coordinate for the tetromino. xOffset depends on the direction that the tetromino is supposed to move in
    bool canMove = true;
    int i, j, col, row;
    for (i = TETROMINO_H - 1; i >= 0; i--)
    {
        for (j = 0; j < TETROMINO_W; j++)
        {
            if (game->activeTetromino.shape[i][j] != 0)
            {
                row = game->activeTetromino.y + i;
                col = newX + j;
                if (col < 0 || col >= GRID_WIDTH || row >= GRID_HEIGHT || (row >= 0 && game->grid[row][col] != 0))			// Checks if the new position is out of bounds or collides with existing blocks
                {
                    canMove = false;
                    break;
                }
            }
        }
        if (!canMove)
        {
            break;
        }
    }
    return canMove;
}
static void clearRows(Game* game)					// Checks for completed rows and clear them
{
    int i, j, k, numClearedRows = 0;
    for (i = GRID_HEIGHT - 1; i >= 0; i--)				//It focuses on one row at a time, throughout the whole grid
    {
        bool isRowFull = true;
        for (j = 0; j < GRID_WIDTH; j++)				//If the row does have every block and no empty spaces, isRowFull keeps its value (true)
        {
            if (game->grid[i][j] == 0)
            {
                isRowFull = false;
                break;
            }
        }
        if (isRowFull)
        {
            for (k = i; k > 0; k--)				            // Shifts all rows above the cleared row down one by one
            {
                for (j = 0; j < GRID_WIDTH; j++)
                {
                    game->grid[k][j] = game->grid[k - 1][j];
                }
            }
            for (j = 0; j < GRID_WIDTH; j++)				// Clears the top row
            {
                game->grid[0][j] = 0;
            }
            numClearedRows++;
            i++;
        }
    }
    updateScore(game, numClearedRows);					//Clearly the score must be updated as well as the game level
    game->lines += numClearedRows;
    updateLevel(game);
}

static bool isGameOver(const Game* game)				// Checks if the game is over by searching for tetromino blocks in the starting position that collide with the game grid
{
	int i, j, row, col;
	for (i = 0; i < TETROMINO_H; i++)				
	{
		for (j = 0; j < TETROMINO_W; j++)
		{
			if (game->activeTetromino.shape[i][j] != 0)		//Gets the tetromino blocks coords, adds the proper off set and checks if the are colliding with the grid
			{
				row = game->activeTetromino.y + i;
				col = game->activeTetromino.x + j;
				if (game->grid[row][col] != 0)
				{
					return true;
				}
			}
		}
	}
    return false;
}

static void updateScore(Game* game, int numClearedRows)			// Updates game score based on the number of rows cleared and the current level
{
    switch (numClearedRows)
    {
	    case 1:
	        game->score += 40 * (game->level + 1);
	        playSoundIndex(BURN);
	        break;
	    case 2:
	        game->score += 100 * (game->level + 1);
	        playSoundIndex(BURN);
	        break;
	    case 3:
	        game->score += 300 * (game->level + 1);
	        playSoundIndex(BURN);
	        break;
	    case 4:
	        game->score += 1200 * (game->level + 1);
	        playSoundIndex(TETRIS);
	        break;
	    default:
	        break;
     }
}
static void updateLevel(Game* game)								// Updates game level. This depends on the required number cleared lines for leveling up (which additionally depends on the current game level)
{
    if (game->lines >= game->levelCheckpoint)
    {
        game->level++;
        game->levelCheckpoint += 10;
		game->hasLevelChanged = true;
    }
}

void generateNewTetromino(Game* game)							// Generates a new random tetromino
{
    int shapeIndex = rand() % NUM_SHAPES;						// Randomly selects a shape index for the new tetromino
    if (game->frames)									// If the game has already started
    {
        if (game->nextTetromino.shapeIndex == I)		       			 // Updates the active tetromino with the new shape and position. Corrects the tetromino initial position
        {
            game->activeTetromino.x = game->nextTetromino.x - 1;
            game->activeTetromino.y = game->nextTetromino.y - 1;
        }
        else
        {
            game->activeTetromino.x = game->nextTetromino.x;
            game->activeTetromino.y = game->nextTetromino.y;
        }
        copyShape(game->nextTetromino.shape, game, true);						//Copies the next tetromino's values to the active
        game->activeTetromino.shapeIndex = game->nextTetromino.shapeIndex;
	game->activeTetromino.shapeIndex = game->nextTetromino.shapeIndex;
	game->activeTetromino.rotation = game->nextTetromino.rotation;
	game->activeTetromino.move_down = game->nextTetromino.move_down;
	game->activeTetromino.move_up = game->nextTetromino.move_up;
	game->activeTetromino.move_left = game->nextTetromino.move_left;
	game->activeTetromino.move_right = game->nextTetromino.move_right;
	game->activeTetromino.rotate_ = game->nextTetromino.rotate_;
        game->statistics[game->nextTetromino.shapeIndex]++;

        game->nextTetromino.x = GRID_WIDTH / 2 - 1;
        game->nextTetromino.y = 0;
        copyShape(tetrominoShapes[shapeIndex][0], game, false);					//Copies the next tetromino shape that was chosen with rand() to the next tetromino shape matrix in the game structure
        game->nextTetromino.shapeIndex = shapeIndex;
    }
    else											//If we still need to create the first active tetromino (in case we are initializing a new game)
    {
        game->nextTetromino.x = GRID_WIDTH / 2 - 1;						// Update the next tetromino with the new shape and position
        game->nextTetromino.y = 0;
        copyShape(tetrominoShapes[shapeIndex][0], game, false);					//Copies the next tetromino shape that was chosen with rand() to the next tetromino shape matrix in the game structure
        game->nextTetromino.shapeIndex = shapeIndex;

        shapeIndex = rand() % NUM_SHAPES;							// Randomly selects a shape index for the new tetromino
        if (shapeIndex == I)									//Corrects the tetromino initial position
        {
            game->activeTetromino.x = GRID_WIDTH / 2 - 2;
            game->activeTetromino.y = -1;
        }
        else
        {
            game->activeTetromino.x = GRID_WIDTH / 2 - 1;
            game->activeTetromino.y = 0;
        }

    	for (int i = 0; i < NUM_SHAPES; i++)							//Clears the shape statistics array
    	{
    		game->statistics[i] = 0;
    	}
        copyShape(tetrominoShapes[shapeIndex][0], game, true);					//Copies another tetromino shape randomly chosen to the active tetromino shape matrix
        game->activeTetromino.move_down = 0;							//Makes sure that the active tetromino does not go down nor rotates before the game starts 
	game->activeTetromino.rotate_ = 0;
	game->activeTetromino.shapeIndex = shapeIndex;						// Updates the new next tetromino with the new shape and position
        game->statistics[shapeIndex]++;								// Updates the shape statistics, according to the tetromino that was generated

    }
    game->nextTetromino.rotation = 0;								//Basic initial values are set for the next tetromino
    game->nextTetromino.move_down = 0;
    game->nextTetromino.move_up = 0;
    game->nextTetromino.move_left = 0;
    game->nextTetromino.move_right = 0;
    game->nextTetromino.rotate_ = 0;
}
static bool canMoveDown(const Game* game)						// Checks if the active tetromino can move down
{
    for (int i = 0; i < TETROMINO_H; i++)						// Checks if any cells below the tetromino are occupied or if it has reached the bottom of the grid
    {
        for (int j = 0; j < TETROMINO_W; j++)
        {
            if (game->activeTetromino.shape[i][j] != 0)
            {
                int row = game->activeTetromino.y + i + 1;
                int col = game->activeTetromino.x + j;
                if (row >= GRID_HEIGHT || game->grid[row][col] != 0)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

static void copyShape(const int source[TETROMINO_H][TETROMINO_W], Game* game, bool active)			// Copies tetromino shape onto either active or next tetromino, depending on the bool active
{
	int i, j;
	if (active)
	{
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
		for (i = 0; i < TETROMINO_H; i++)
		{
			for (j = 0; j < TETROMINO_W; j++)
			{
				game->nextTetromino.shape[i][j] = source[i][j];
			}
		}
	}
}

static void fixTetromino(Game* game)						// Fixes the tetromino in its current position on the game grid
{
	int i, j;
	for (i = 0; i < TETROMINO_H; i++)						// Updates the game grid with the tetromino's occupied cells
	{
		for (j = 0; j < TETROMINO_W; j++)
		{
			if (game->activeTetromino.shape[i][j] != 0)
			{
				int row = game->activeTetromino.y + i;
				int col = game->activeTetromino.x + j;
				game->grid[row][col] = 1;
				updateColorMap(game, row, col);
			}
		}
	}
	playSoundIndex(FIX);
}

static void rotate(Game* game)									// Checks if the new rotation is valid, if it is, it is done
{
	int oldRotation = game->activeTetromino.rotation;
	int newRotation = (oldRotation + 1) % 4;						
	bool canRotate = true;
	int i;
	int j;
	for (i = 0; i < TETROMINO_H; i++)
	{
		for (j = 0; j < TETROMINO_W; j++)
		{
			if (tetrominoShapes[game->activeTetromino.shapeIndex][newRotation][i][j] != 0)
			{
				int row = game->activeTetromino.y + i;
				int col = game->activeTetromino.x + j;
				if (col < 0 || col >= GRID_WIDTH || row <= -1 || row >= GRID_HEIGHT || (row >= 0 && game->grid[row][col] != 0))			//Checks if the rotated tetromino blocks are well located or they exceed the limits of grid/collide with it
				{
					canRotate = false;						//As the tetromino cannot rotate, the program must leave this section
					j = TETROMINO_W;						//Conditions to leave both of the for cycles
					i = TETROMINO_H;
				}
			}
		}
	}
	if (canRotate)	
	{
		game->activeTetromino.rotation = newRotation;						//Since there is no problem with the new rotation, it is updated.
		for (i = 0; i < TETROMINO_H; i++)
		{
			for (j = 0; j < TETROMINO_W; j++)
			{
				game->activeTetromino.shape[i][j] = tetrominoShapes[game->activeTetromino.shapeIndex][newRotation][i][j];
			}
		}
		game->activeTetromino.rotate_--;
		playSoundIndex(ROTATE);
	}
	else
	{
		game->activeTetromino.rotate_ = 0;							//In case it could not be rotated, the rotation buffer is cleared
	}
}
static void updateColorMap(Game* game, int row, int col)						//Makes that the recently fixed tetromino maintains its color 
{
	#ifdef PC
	switch (game->activeTetromino.shapeIndex)
	{
		case I:
		case O:
		case T:
			game->tetrominoGrid[row][col] = BLOCK_TYPES * (game->level % LEVEL_STYLES) + WHITE;
			break;
		case L:
		case Z:
			game->tetrominoGrid[row][col] = BLOCK_TYPES * (game->level % LEVEL_STYLES) + LIGHT;
			break;
		case J:
		case S:
			game->tetrominoGrid[row][col] = (BLOCK_TYPES * game->level % LEVEL_STYLES) + DARK;
			break;
	}
	#endif
}




