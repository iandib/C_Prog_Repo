/***************************************************************************//**
  @file     +handler.c
  @brief    +Handling functions
  @author   +Helou, Luchelli, Segura
 ******************************************************************************/

 /*******************************************************************************
  * INCLUDE HEADER FILES
  ******************************************************************************/

#include "handler.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/



/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static void falta_envido (int);+


/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static int temperaturas_actuales[4];+

/*******************************************************************************
 *******************************************************************************
                    GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/


void initializeElements()
{
#ifdef PC
    initializeAllegro();
#else
	initializeRaspy();
#endif
}

void destroyElements()
{
#ifdef PC
    destroyAllegro();
#else
	destroyRaspy();
#endif
}

void updateHud(Game* game)
{
#ifdef PC
    allegroUpdateHud(game);
#endif
}

void drawHud(Game* game)
{
#ifdef PC
    allegroDrawHud(game);
#else
	showLevel(game);
	showNext(game);
#endif
}

// --- drawing ---

void drawMenu()
{
#ifdef PC
	allegroDrawMenu();
#endif
}

// Draws current state of the game

void drawGame(const Game* game)
{
    // Draws static tetrominos
    drawGrid(game);

    // Draws active tetromino
    drawActiveTetromino(game);
}

// Draws static tetrominos

void drawGrid(const Game* game)
{
#ifdef PC
    allegroDrawGrid(game);
#else
	draw_board(game);
#endif
}

// Draws active tetromino

void drawActiveTetromino(const Game* game)
{
#ifdef PC
    allegroDrawActiveTetromino(game);
#else
	draw_tetromino(game);
#endif
}

// Draws game over message

void drawGameOver(long score)
{
#ifdef PC
    allegroDrawGameOver(score);
#else
	raspyShowScore(score);
#endif
}

void drawNewHighScore(long score, int scoreIndex)
{
#ifdef PC
    allegroDrawHighScore(score, scoreIndex);
#endif
}

void drawPause(Game* game)
{
#ifdef PC
    allegroDrawPause();
#endif
}

void drawUpdatedScore()
{
#ifdef PC
    allegroGetTopScore();
#endif
}

bool movedLeft()
{
#ifdef PC
    if (allegro->key[ALLEGRO_KEY_LEFT])
        return true;
    else
        return false;
#else
	jcoord_t coord = joy_get_coord();
    if (coord.x < JOY_MAX_NEG/2){
    	return true;
    }
    else 
    	return false;
#endif
}

bool movedRight()
{
#ifdef PC
    if (allegro->key[ALLEGRO_KEY_RIGHT])
        return true;
    else
        return false;
#else
	jcoord_t coord = joy_get_coord();
    if (coord.x > JOY_MAX_POS/2){
    	return true;
    }
    else 
    	return false;
#endif
}

bool movedDown()
{
#ifdef PC
    if (allegro->key[ALLEGRO_KEY_DOWN])
        return true;
    else
        return false;
#else
	jcoord_t coord = joy_get_coord();
	if (coord.y < JOY_MAX_NEG/2){
		return true;
	}
	else
    	return false;
#endif
}

bool movedUp()
{
#ifdef PC
    if (allegro->key[ALLEGRO_KEY_UP])
        return true;
    else
        return false;
#else
	jcoord_t coord = joy_get_coord();
	if (coord.y > JOY_MAX_POS / 2)
	{
		return true;
	}
	else
	{
		return false;
	}
#endif
}

bool rotated()
{
#ifdef PC
    if (allegro->key[ALLEGRO_KEY_SPACE])
        return true;
    else
        return false;
#else
	jswitch_t state = joy_get_switch();
	if (state == J_PRESS){
		return true;
	}
    return false;
#endif
}

void updateColorMap(Game* game, int row, int col)
{
#ifdef PC
    allegroUpdateColorMap(game, row, col);
#endif
}

void playSoundIndex(int soundIndex)
{
#ifdef PC
    allegroPlaySound(soundIndex);
#else
	raspyPlaySound(soundIndex);
#endif
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
