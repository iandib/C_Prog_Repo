/***************************************************************************//**
  @file     +handler.h
  @brief    +handling functions
  @author   +Helou, Luchelli, Segura
 ******************************************************************************/

#ifndef _HANDLER_H_
#define _HANDLER_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdbool.h>

#include "common.h"

#ifdef PC
#include "allegro.h"
#else
#include "raspy.h"
#include "disdrv.h"  // Archivo de cabecera del display
#include "joydrv.h"   // Archivo de cabecera del joystick
#endif

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/



/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// --- Allegro ---
#ifdef PC
extern ALLEGRO_ELEMENTS* allegro;
#endif


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
* @brief Initializes necesary elements
*/
void initializeElements();
/**
* @brief Destroys necesary elements
*/
void destroyElements();


// --- hud ---
/**
* @brief Draws heads up display
* @param game Pointer to the game structure
*/
void drawHud(Game* game);

/**
* @brief Updates heads up display statitstics
* @param game Pointer to the game structure
*/
void updateHud(Game* game);


// --- drawing ---
/**
* @brief Draws the whole game
* @param game Pointer to the game structure
*/
void drawGame(const Game* game);

/**
* @brief Draws fixed tetrominos
* @param game Pointer to the game structure
*/
void drawGrid(const Game* game);

/**
* @brief Draws active tetromino
* @param game Pointer to the game structure
*/
void drawActiveTetromino(const Game* game);

/**
* @brief Draws game over screen
* @param score Final game score
*/
void drawGameOver(long score);

/**
* @brief Draws pause screen
* @param game Pointer to the game structure
*/
void drawPause(Game* game);

/**
* @brief Draws new high score message
* @param score New high score
* @param scoreIndex Position on the leaderboard of the new high score
*/
void drawNewHighScore(long score, int scoreIndex);

/**
* @brief Draws updated top score if beaten on the previous game
*/
void drawUpdatedScore();

/**
* @brief Updates color map of the fixed tetrominos
* @param game Pointer to the game structure
* @param row Row of the position to be updated
* @param col Column of the position to be updated
*/
void updateColorMap(Game* game, int row, int col);


// --- sound ---

/**
* @brief Plays requested sound
* @param soundIndex Index of the sound to be played
*/
void playSoundIndex(int soundIndex);

// --- drawing ---
/**
* @brief Draws the menu screen
*/
void drawMenu();


// --- movement ---

/**
* @brief checks if the player moved to the left
* @return Returns true if the player moved to the left
*/
bool movedLeft();

/**
* @brief checks if the player moved to the right
* @return Returns true if the player moved to the right
*/
bool movedRight();

/**
* @brief checks if the player moved down
* @return Returns true if the player moved down
*/
bool movedDown();

/**
* @brief checks if the player moved up
* @return Returns true if the player moved up
*/
bool movedUp();

/**
* @brief checks if the player rotated the tetromino
* @return Returns true if the player rotated the tetromino
*/
bool rotated();

/*******************************************************************************
 ******************************************************************************/

#endif // _HANDLER_H_
