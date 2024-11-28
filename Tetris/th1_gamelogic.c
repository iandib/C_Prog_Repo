/*
 * th1_gamelogic.c
 *
 *  Created on: Nov 25, 2024
 *      Author: juani
 */
#include <stdbool.h>
#include <stdio.h>
#include "common.h"
#include "th2_display_sound.h"
#include <time.h>
#include <stdlib.h>
#include <semaphore.h>
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define PC true

#define BLOCK_TYPES 4
#define LEVEL_STYLES 10

#define NUM_SHAPES 7
#define TETROMINO_W 4
#define TETROMINO_H 4
#define TETROMINO_R 4

#define GRID_WIDTH 10

#ifdef PC
#define GRID_HEIGHT 20
#else
#define GRID_HEIGHT 16
#endif

#define FPS 60
#define KEY_DELAY FPS/10

#ifdef PC
#define FIX_DELAY 10
#else
#define FIX_DELAY 5
#endif

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
static bool canMoveSideways(Game* game, int xOffset);
static bool canMoveDown(const Game* game);
static bool isGameOver(const Game* game);
static void updateScore(Game* game, int numClearedRows);
static void clearRows(Game* game);
static void fixTetromino(Game* game);
static void updateColorMap(Game* game, int row, int col);
static void updateLevel(Game* game);

void initializeGame(Game* game);
void * th1_gamelogic(void* gamep);
void generateNewTetromino(Game* game);

extern int tetrominoShapes[NUM_SHAPES][TETROMINO_R][TETROMINO_H][TETROMINO_W];
extern sem_t s;

void * th1_gamelogic(void* gamep)
{
	Game* game = gamep;
	initializeGame(game);
	initialize_leaderboard(game);
    FILE* save = fopen("saving.txt", "r");
    if(save != NULL){
    	fclose(save);
		game->pause = true;
		recover_game(game);
	}
    else
	{
    	game->menu = true;
	}
	srand(time(NULL));
	//generateNewTetromino(game);
	while(!game->quit)
	{
		if(!game->menu && !game->pause && !game->gameOver)
		{
			if(game->activeTetromino.move_down)
			{
				if(canMoveDown(game))
				{
					game->activeTetromino.y++;
					game->activeTetromino.move_down--;						//Moves tetromino
				}
				else
				{
					game->activeTetromino.move_down = 0;
					game->fixDelay += 0;
					// Fixes the tetromino in its current position on the game grid
					fixTetromino(game);

					// Checks for completed rows and clear them
					clearRows(game);

					// Generates a new random tetromino shape and position
					generateNewTetromino(game);

				}
			}
			else if(game->activeTetromino.move_left)
			{
				if (canMoveSideways(game, -1))
				{								 					// Moves tetromino left
					game->activeTetromino.x--;
					game->activeTetromino.move_left--;
					playSoundIndex(MOVE_SIDEWAYS);
				}
				else
				{
					game->activeTetromino.move_left = 0;
				}
			}
			else if(game->activeTetromino.move_right)
			{
				if (canMoveSideways(game, 1))
				{														 // Moves tetromino right
					game->activeTetromino.x++;
					game->activeTetromino.move_right--;
					playSoundIndex(MOVE_SIDEWAYS);
				}
				else
				{
					game->activeTetromino.move_right = 0;
				}
			}
			else if(game->activeTetromino.rotate_)
			{
				int oldRotation = game->activeTetromino.rotation;
				int newRotation = (oldRotation + 1) % 4;
				// Checks if the new rotation is valid
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
							if (col < 0 || col >= GRID_WIDTH || row <= -1 || row >= GRID_HEIGHT || (row >= 0 && game->grid[row][col] != 0))
							{
								canRotate = false;
								break;
							}
						}
					}
					if (!canRotate)
					{
						break;
					}
				}
				if (canRotate)
				{
					// Updates the rotation of the tetromino
					game->activeTetromino.rotation = newRotation;
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
			}
		    if (game->lines >= game->levelCheckpoint)
		    {
		        game->level++;
		        game->levelCheckpoint += 10;
		    }
		    if (isGameOver(game))
		    {
		        game->gameOver = true;
		        if (!game->waitingForExit)
		        {
		            game->waitingForExit = true;
		            playSoundIndex(GAME_OVER);
		            //update_leaderboard(game);
		        }
		    }
			game->redraw = true;
			game->frames++;
		}
		else
		{
			//initializeGame(game);
			if(game->menu || game->gameOver)
			{
				generateNewTetromino(game);
			}
			sem_wait(&s);
		}
	}
	pthread_exit(0);
}

void initializeGame(Game* game)
{
    // Seed random number generator
	/*#ifdef PC
	if (!game->frames)
	{
		game->menu = true;
	}
	else
	{
		game->menu = false;
	}
	#else
	game->menu = true;*/
	//#endif
	//game->grid[10][0] = 6;
	game->gameOver = false;
	game->frames = 0;
	game->score = 0;
	game->highScoreIndex = 0;
	game->level = 0;
	game->lines = 0;
	game->levelCheckpoint = 1 * (game->level + 1);
	game->fixDelay = 0;
	game->waitingForExit = false;
	game->quit = false;
	game->pause = false;
	game->redraw = true;

	//initialize_leaderboard(game);
	int i;
	for (i = 0; i < NUM_SHAPES; i++)
	{
		game->statistics[i] = 0;
	}

	// Initialize the game grid with zeros
	for (i = 0; i < GRID_HEIGHT; i++)
	{
		for (int j = 0; j < GRID_WIDTH; j++)
		{
			game->grid[i][j] = 0;
			game->tetrominoGrid[i][j] = 0;
		}
	}
    for (i = 0; i < TETROMINO_H; i++)
    {
        for (int j = 0; j < TETROMINO_W; j++)
        {
            game->activeTetromino.shape[i][j] = 0;

        }
    }
}
static bool canMoveSideways(Game* game, int xOffset)
{
    // Calculate the new x coordinate for the tetromino
    int newX = game->activeTetromino.x + xOffset;

    // Check if the tetromino can move horizontally in the specified direction
    bool canMove = true;
    //int rotation = game->activeTetromino.rotation;

    int i;
    int j;
    for (i = TETROMINO_H - 1; i >= 0; i--)
    {
        for (j = 0; j < TETROMINO_W; j++)
        {
            if (game->activeTetromino.shape[i][j] != 0)
            {
                int row = game->activeTetromino.y + i;
                int col = newX + j;

                // Check if the new position is out of bounds or collides with existing blocks
                if (col < 0 || col >= GRID_WIDTH || row >= GRID_HEIGHT || (row >= 0 && game->grid[row][col] != 0))
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

// Checks for completed rows and clear them
static void clearRows(Game* game)
{
    int numClearedRows = 0;
    int i;
    int j;
    int k;
    for (i = GRID_HEIGHT - 1; i >= 0; i--)
    {
        bool isRowFull = true;
        for (j = 0; j < GRID_WIDTH; j++)
        {
            if (game->grid[i][j] == 0)
            {
                isRowFull = false;
                break;
            }
        }
        if (isRowFull)
        {
            // Shift all rows above the cleared row down by one
            for (k = i; k > 0; k--)
            {
                for (j = 0; j < GRID_WIDTH; j++)
                {
                    game->grid[k][j] = game->grid[k - 1][j];
                }
            }
            // Clear the top row
            for (j = 0; j < GRID_WIDTH; j++)
            {
                game->grid[0][j] = 0;
            }
            numClearedRows++;
            i++;
        }
    }
    updateScore(game, numClearedRows);
    game->lines += numClearedRows;
    if (numClearedRows)
    {
        updateLevel(game);
    }
}

// Checks if the game is over
static bool isGameOver(const Game* game)
{
    if (!game->fixDelay)
    {
        int i;
        int j;
        // Checks if any cells in the starting position are occupied

        for (i = 0; i < TETROMINO_H; i++)
        {
            for (j = 0; j < TETROMINO_W; j++)
            {
                if (game->activeTetromino.shape[i][j] != 0)
                {
                    int row = game->activeTetromino.y + i;
                    int col = game->activeTetromino.x + j;
                    if (game->grid[row][col] != 0)
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// Updates game score based on the number of rows cleared and the current level
static void updateScore(Game* game, int numClearedRows)
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

// Updates game level

static void updateLevel(Game* game)
{
    if (game->lines >= game->levelCheckpoint)
    {
        game->level++;
        game->levelCheckpoint += 10;
    }
}
// Generate a new random tetromino
void generateNewTetromino(Game* game)
{
    // Randomly select a shape index for the new tetromino
    int shapeIndex = rand() % NUM_SHAPES;
    if (game->frames)
    {
        // Update the active tetromino with the new shape and position

        if (game->nextTetromino.shapeIndex == I)
        {
            game->activeTetromino.x = game->nextTetromino.x - 1;
            game->activeTetromino.y = game->nextTetromino.y - 1;
        }
        else
        {
            game->activeTetromino.x = game->nextTetromino.x;
            game->activeTetromino.y = game->nextTetromino.y;
        }
        copyShape(game->nextTetromino.shape, game, true);
        game->activeTetromino.shapeIndex = game->nextTetromino.shapeIndex;
        game->activeTetromino.rotation = game->nextTetromino.rotation;
        game->activeTetromino.move_down = game->nextTetromino.move_down;
        game->activeTetromino.move_up = game->nextTetromino.move_up;
        game->activeTetromino.move_left = game->nextTetromino.move_left;
        game->activeTetromino.move_right = game->nextTetromino.move_right;
        game->activeTetromino.rotate_ = game->nextTetromino.rotate_;

        game->statistics[game->nextTetromino.shapeIndex]++;

        // Update the active tetromino with the new shape and position
        game->nextTetromino.x = GRID_WIDTH / 2 - 1;
        game->nextTetromino.y = 0;
        copyShape(tetrominoShapes[shapeIndex][0], game, false);
        game->nextTetromino.shapeIndex = shapeIndex;
    }
    else
    {
        // Update the active tetromino with the new shape and position
        game->nextTetromino.x = GRID_WIDTH / 2 - 1;
        game->nextTetromino.y = 0;
        copyShape(tetrominoShapes[shapeIndex][0], game, false);
        game->nextTetromino.shapeIndex = shapeIndex;

        // Randomly select a shape index for the new tetromino
        shapeIndex = rand() % NUM_SHAPES;

        // Update the active tetromino with the new shape and position
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
        copyShape(tetrominoShapes[shapeIndex][0], game, true);
        game->activeTetromino.shapeIndex = shapeIndex;
        game->activeTetromino.rotation = 0;
        game->activeTetromino.move_down = 0;
        game->activeTetromino.move_up = 0;
        game->activeTetromino.move_left = 0;
        game->activeTetromino.move_right = 0;
        game->activeTetromino.rotate_ = 0;
        game->statistics[shapeIndex]++;
    }
    game->nextTetromino.rotation = 0;
    game->nextTetromino.move_down = 0;
    game->nextTetromino.move_up = 0;
    game->nextTetromino.move_left = 0;
    game->nextTetromino.move_right = 0;
    game->nextTetromino.rotate_ = 0;
}

// Checks if the active tetromino can move down
static bool canMoveDown(const Game* game)
{
    int i;
    int j;
    // Checks if any cells below the tetromino are occupied or if it has reached the bottom

    for (i = 0; i < TETROMINO_H; i++)
    {
        for (j = 0; j < TETROMINO_W; j++)
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

// Copies tetromino shape onto either active or next tetromino
static void copyShape(const int source[TETROMINO_H][TETROMINO_W], Game* game, bool active)
{
    int i;
    int j;
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

// Fixes the tetromino in its current position on the game grid
static void fixTetromino(Game* game)
{
    int i;
    int j;
    // Updates the game grid with the tetromino's occupied cells
    for (i = 0; i < TETROMINO_H; i++)
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

static void updateColorMap(Game* game, int row, int col)
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
				game->tetrominoGrid[row][col] = (BLOCK_TYPES * (game->level % LEVEL_STYLES)) + LIGHT;
				break;
			case J:
			case S:
				game->tetrominoGrid[row][col] = (BLOCK_TYPES * (game->level % LEVEL_STYLES)) + DARK;
				break;
	    }
	#endif
}


