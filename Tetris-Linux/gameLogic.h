/***************************************************************************//**
  @file     +gameLogic.h
  @brief    +Common constants and functions
  @author   +Helou, Luchelli, Segura
 ******************************************************************************/

#ifndef _GAME_LOGIC_H_
#define _GAME_LOGIC_H_

 /*******************************************************************************
  * INCLUDE HEADER FILES
  ******************************************************************************/

#include <stdlib.h>
#include "common.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/



/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

extern int tetrominoShapes[NUM_SHAPES][TETROMINO_R][TETROMINO_H][TETROMINO_W];

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

 /**
  * @brief Menu loop
  * @param game Pointer to the game structure
  */
void menuLoop(Game* game);

/**
 * @brief Game loop
 * @param game Pointer to the game structure
 */
void gameLoop(Game* game);

/**
 * @brief Gets game ready to be played
 * @param game Pointer to the game structure
 */
void initializeGame(Game* game);

/**
 * @brief Updates game state
 * @param game Pointer to the game structure
 */
void updateGame(Game* game);

/**
 * @brief Updates active tetromino position
 * @param game Pointer to the game structure
 */
void updateMovement(Game* game);

/**
 * @brief Updates game score based on cleared rows and level
 * @param game Pointer to the game structure
 * @param numClearedRows Number of rows cleared
 */
void updateScore(Game* game, int numClearedRows);

/**
 * @brief Updates game level based on number of cleared rows
 * @param game Pointer to the game structure
 */
void updateLevel(Game* game);

/**
 * @brief Checks if the game is over
 * @param game Pointer to the game structure
 * @return Returns true if the game is over, false otherwise
 */
bool isGameOver(const Game* game);

/**
 * @brief Updates leaderboard after a game
 * @param game Pointer to the game structure
 */

/**
 * @brief Checks if the active tetromino can move down
 * @param game Pointer to the game structure
 * @return Returns true if the active tetromino can move down, false otherwise
 */
bool canMoveDown(const Game* game);

/**
 * @brief Fixes active tetromino in its current position
 * @param game Pointer to the game structure
 */
void fixTetromino(Game* game);

/**
 * @brief Clears full rows
 * @param game Pointer to the game structure
 */
void clearRows(Game* game);

/**
 * @brief Generates a new random tetromino
 * @param game Pointer to the game structure
 */
void generateNewTetromino(Game* game);

/**
 * @brief Checks if the active tetromino can move sideways
 * @param game Pointer to the game structure
 * @param xOffset Movement direction and ammount to be checked
 * @return Returns true if the tetromino can move where it needs to, false otherwise
 */
bool canMoveSideways(Game* game, int xOffset);

/**
 * @brief Rotates active tetromino
 * @param game Pointer to the game structure
 */
void rotateTetromino(Game* game);



/*******************************************************************************
 ******************************************************************************/

#endif // _GAME_LOGIC_H_
