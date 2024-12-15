/* *****************************************************************
    *                    HEADER CONFIGURATION                     *
   ***************************************************************** */

// We make sure the header is only included once 
#ifndef GAME_LOGIC_h
#define GAME_LOGIC_h

/* ---------------------- NECESSARY HEADERS ------------------------ */

// Header containing common definitions shared across the game
#include "utilities.h"

/* ---------------------- MACROS & CONSTANTS ---------------------- */

// ??
#define BLOCK_TYPES 4

// ??
#define LEVEL_STYLES 10

/* ---------------------- STRUCTURES & ENUMS ---------------------- */

// Color codes for the different block types
enum blockTypes
{
    WHITE = 0,
    LIGHT,
    DARK,
    STRIPES
};

/* ----------------- PUBLIC FUNCTIONS PROTOTYPES ----------------- */

// Contains the main game logic executed by thread 1
void * th1_gamelogic(void* gamep);

// Initializes the game state with default values
void initializeGame(Game* game);

// Generates a new random tetromino and updates game statistics
void generateNewTetromino(Game* game);

#endif // GAME_LOGIC_h
