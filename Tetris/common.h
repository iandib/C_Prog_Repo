#ifndef _COMMON_H_
#define _COMMON_H_

 /*******************************************************************************
  * INCLUDE HEADER FILES
  ******************************************************************************/
 
#include <stdbool.h>
#include <pthread.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

//#define PC true

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
#define KEY_DELAY -15

#ifdef PC
#define FIX_DELAY 10
#else
#define FIX_DELAY 5
#endif

 /*******************************************************************************
  * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
  ******************************************************************************/

  // Enums

enum tetrominoShapeIndex {
    L = 0,
    J,
    I,
    O,
    T,
    S,
    Z
};

enum SFXIndex
{
    BURN,
    TETRIS,
    MOVE_SIDEWAYS,
    ROTATE,
    FIX,
    GAME_OVER,
    VICTORY
};

// Typedefs

typedef struct {
    int x;
    int y;
    int rotation;
    int shape[TETROMINO_H][TETROMINO_W];
    int shapeIndex;
    int move_down;			//Add to the recover/save functions!!!
    int move_up;
    int move_left;
    int move_right;
    int rotate_;
} Tetromino;

typedef struct{
	char name[4];
	int score;
} player_t;

typedef struct {
    int grid[GRID_HEIGHT][GRID_WIDTH]; // Game grid		-SAVE
    int tetrominoGrid[GRID_HEIGHT][GRID_WIDTH]; // Specific tetromino block grid	-SAVE
    Tetromino activeTetromino; // Active tetromino		-SAVE
    Tetromino nextTetromino; // Next tetromino			-SAVE
    long score; // Score								-SAVE
    int highScoreIndex; // Highscore index
    player_t leaderboard[11];	//Leaves an space at the end to store the current player data
    int level; // Level						-SAVE
    bool hasLevelChanged; /*flag to check whether the level has been upgraded.
                         It is declared here to avoid using global variables unnecesarely */
    bool gameOver; // Game over flag
    long frames; // Frame counter
    int lines; // Cleared lines counter
    int levelCheckpoint; // Level checkpoint
    int fixDelay; // Bottom row movement buffer	//SACO
    bool quit; // Quit flag
    bool pause; // Pause flag
    bool redraw; // Redraw flag
    bool waitingForExit; // Waiting for exit flag	//SACO
    bool menu; // Menu flag
    int statistics[NUM_SHAPES]; // Statistics
}Game;

#endif // _COMMON_H_
