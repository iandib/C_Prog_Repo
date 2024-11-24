/***************************************************************************//**
  @file     +common.h
  @brief    +Common constants and functions
  @author   +Helou, Luchelli, Segura
 ******************************************************************************/

#ifndef _COMMON_H_
#define _COMMON_H_

 /*******************************************************************************
  * INCLUDE HEADER FILES
  ******************************************************************************/

#include <stdbool.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define PC true

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
    int moveTimer;
    int rotateTimer;
} Tetromino;

typedef struct {
    int grid[GRID_HEIGHT][GRID_WIDTH]; // Game grid
    int tetrominoGrid[GRID_HEIGHT][GRID_WIDTH]; // Specific tetromino block grid
    Tetromino activeTetromino; // Active tetromino
    Tetromino nextTetromino; // Next tetromino
    long score; // Score
    int highScoreIndex; // Highscore index
    int level; // Level
    bool gameOver; // Game over flag
    long frames; // Frame counter
    int lines; // Cleared lines counter
    int levelCheckpoint; // Level checkpoint
    int fixDelay; // Bottom row movement buffer
    bool quit; // Quit flag
    bool pause; // Pause flag
    bool redraw; // Redraw flag
    bool waitingForExit; // Waiting for exit flag
    bool menu; // Menu flag
    int statistics[NUM_SHAPES]; // Statistics
} Game;

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

 // +ej: extern unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
* @brief Copies tetromino shape onto either active or next tetromino
* @param source Tetromino shape to be copied
* @param game Pointer to game structure
* @param active Whether the shape is to be copied onto the active tetromino or the next tetromino
*/
void copyShape(const int source[TETROMINO_H][TETROMINO_W], Game* game, bool active);


/*******************************************************************************
 ******************************************************************************/

#endif // _COMMON_H_
