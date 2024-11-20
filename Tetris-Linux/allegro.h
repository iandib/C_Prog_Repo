/***************************************************************************//**
  @file     +allegro.h
  @brief    +Allegro constants and functions
  @author   +Helou, Luchelli, Segura
 ******************************************************************************/


#ifndef _ALLEGRO_H
#define _ALLEGRO_H

 /*******************************************************************************
  * INCLUDE HEADER FILES
  ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "common.h"

#ifdef PC

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

// --- sprites ---
#define BLOCK_TYPES 4
#define LEVEL_STYLES 10

// --- sound ---

#define MAX_SFX 32

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

// --- sprites ---
enum blockTypes 
{
    WHITE = 0,
    LIGHT,
    DARK,
    STRIPES
};

typedef struct 
{
    ALLEGRO_BITMAP* _sheet;

    ALLEGRO_BITMAP* blocks[LEVEL_STYLES][BLOCK_TYPES];

    ALLEGRO_BITMAP* level;

    ALLEGRO_BITMAP* hud;

    ALLEGRO_BITMAP* menu;

} SPRITES;

// --- allegro ---
typedef struct 
{
    // event queue
    ALLEGRO_EVENT_QUEUE* eventQueue;

    unsigned char key[ALLEGRO_KEY_MAX];

    // display
    ALLEGRO_DISPLAY* display;
    ALLEGRO_BITMAP* buffer;

    // hud
    ALLEGRO_FONT* font;
    long score_display;

    // sound 
    ALLEGRO_SAMPLE* SFX[MAX_SFX];
    ALLEGRO_AUDIO_STREAM* music;

    // sprites
    SPRITES sprites;

    // timer
    ALLEGRO_TIMER* timer;

    // score
    long topScore;
    int scoreIndex;

} ALLEGRO_ELEMENTS;



/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

extern int tetrominoShapes[NUM_SHAPES][TETROMINO_R][TETROMINO_H][TETROMINO_W];

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// --- allegro ---
 /**
  * @brief Initializes all necesary Allegro elements
  */
void initializeAllegro(Game* game);

/**
 * @brief Destroys all necesary Allegro elements
 */
void destroyAllegro();


// --- keyboard ---
/**
 * @brief Handles keyboard events
 * @param event Allegro event to be registered
 */
void allegroUpdateKeyboard(ALLEGRO_EVENT* event);


// --- display ---
/**
 * @brief Primes bitmap for drawing the next frame
 * @param buffer Allegro bitmap to be primed
 */
void allegroDisplayPreDraw(ALLEGRO_BITMAP* buffer);

/**
 * @brief Shows the drawn frame
 * @param display Display to be shown on
 * @param buffer Drawn bitmap to be shown
 */
void allegroDisplayPostDraw(ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* buffer);


// --- drawing ---
/**
 * @brief Draws menu screen
 */
void allegroDrawMenu();

/**
 * @brief Draws fixed tetrominos
 * @param game Pointer to the game structure
 */
void allegroDrawGrid(const Game* game);

/**
 * @brief Draws active tetromino
 * @param game Pointer to the gae structure
 */
void allegroDrawActiveTetromino(const Game* game);

/**
 * @brief Draws game over screen
 * @param score Final game score
 */
void allegroDrawGameOver(long score);

/**
 * @brief Draws pause screen
 */
void allegroDrawPause();

/**
 * @brief Draws new high score if needed
 * @param score New high score
 * @param scoreIndex Position on the leaderboard of the new high score
 */
void allegroDrawHighScore(long score, int scoreIndex);

/**
 * @brief Updates the color map of the fixed tetrominos
 * @param game Pointer to the game structure
 * @param row Row of the position to be updated
 * @param col Column of the position to be updated
 */
void allegroUpdateColorMap(Game* game, int row, int col);


// --- hud ---
/**
 * @brief Draws heads up display
 * @param game Pointer to the game structure
 */
void allegroDrawHud(Game* game);

/**
 * @brief Updates heads up display values
 * @param game Pointer to the game structure
 */
void allegroUpdateHud(Game* game);


// --- sound ---
/**
 * @brief Plays requested sound
 * @param soundIndex Index of the sound to be played
 */
void allegroPlaySound(int soundIndex);

// --- score ---
/**
 * @brief Fetches the top score from the leaderboard
 */
void allegroGetTopScore(Game* game);

#endif // PC

#endif // _ALLEGRO_H
