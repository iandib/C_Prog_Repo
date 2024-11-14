/***************************************************************************//**
  @file     +raspy.c
  @brief    +raspy game functions
  @author   +Helou, Luchelli, Segura
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "common.h"

#ifndef PC
#include "raspy.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <SDL2/SDL.h>


/***************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 **************************/

#define GAME "music1.wav"
#define LINE "burn.wav"
#define LOSE "gameOver.wav"
#define MOVE "moveSideways.wav"
#define ROT "rotate.wav"
#define LEVEL "tetris.wav"

/***************************
 * VARIABLES WITH GLOBAL SCOPE
 **************************/

char * raspySoundArray [10] = {0};
char** raspySounds = &raspySoundArray;


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
 
// Función para dibujar el tablero en el display
void draw_board(Game* game) {
    dcoord_t coords;
	for(int i = 0;i < GRID_HEIGHT;i++)
	{
		for(int j = 0;j < GRID_WIDTH;j++)
		{
			if(game->grid[i][j])
			{   
                coords.x = j;
                coords.y = i;
                if(coords.x >= 0 && coords.x <= DISP_MAX_X && coords.y >= 0 && coords.y <= DISP_MAX_Y){
                    disp_write(coords,D_ON);
                }
			}
            else
            {
                coords.x = j;
                coords.y = i;
                if(coords.x >= 0 && coords.x <= DISP_MAX_X && coords.y >= 0 && coords.y <= DISP_MAX_Y){
                    disp_write(coords,D_OFF);
                }
            }
		}
	}
    disp_update();
}

void draw_tetromino(Game* game)
{
    dcoord_t coords;
	for(int i = 0;i < TETROMINO_H;i++)
	{
		for(int j = 0;j < TETROMINO_W;j++)
		{
			if(game->activeTetromino.shape[i][j])
			{   
                coords.x = j+game->activeTetromino.x;
                coords.y = i+game->activeTetromino.y;
                if(coords.x >= 0 && coords.x <= DISP_MAX_X && coords.y >= 0 && coords.y <= DISP_MAX_Y){
                    disp_write(coords,D_ON);
                }
			}
		}
	}
    disp_update();
}

void moveSideways (Game* game) {
	jcoord_t coord = joy_get_coord();
    if(movedRight() && canMoveSideways(game,1))
    {
    	playSound(MOVE,SDL_MIX_MAXVOLUME);
    	game->activeTetromino.x++;
    }
    else if(movedLeft() && canMoveSideways(game,-1))
    {
    	playSound(MOVE,SDL_MIX_MAXVOLUME);
    	game->activeTetromino.x--;
    }
}

void joyUpdateValues (){
    joy_update();
}

void clearDisp (){
    disp_clear();
}

void rotate (Game* game) {
	jswitch_t state = joy_get_switch();

	if(rotated())
	{
		playSound(ROT,SDL_MIX_MAXVOLUME);
		rotateTetromino(game);
	}
}

void showNext (Game* game)
{
    dcoord_t coords;
    for(int i = 0;i < TETROMINO_H;i++)
	{
		for(int j = 0;j < TETROMINO_W;j++)
		{
            coords.x = j+11;
            coords.y = i;
			disp_write(coords,D_OFF);
		}
	}
	for(int i = 0;i < TETROMINO_H;i++)
	{
		for(int j = 0;j < TETROMINO_W;j++)
		{
			if(game->nextTetromino.shape[i][j])
			{   
                coords.x = j+11;
                coords.y = i;
				disp_write(coords,D_ON);
			}
		}
	}
    disp_update();
}

void showLevel (Game* game)
{
	int x = 11;
    dcoord_t coords;
    coords.x = x + game->level%5;
    coords.y = 10 + (int)game->level/5;
	disp_write(coords,D_ON);
    disp_update();
}

bool checkPasue ()
{
    jcoord_t coord = joy_get_coord();
    if(coord.y > JOY_MAX_POS/2) 
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool checkQuit ()
{
    jswitch_t state = joy_get_switch();
    if(state) 
    {
    	pauseAudio();
        return true;
    }
    else
    {
        return false;
    }
}



void moveTetromino (Game* game)
{
    jcoord_t coord = joy_get_coord();
    if (movedDown() && canMoveDown(game))
    {
    	playSound(MOVE,SDL_MIX_MAXVOLUME);
        game->activeTetromino.y++;
    }
}

bool checkResume ()
{
    jcoord_t coord = joy_get_coord();
    if(coord.x < JOY_MAX_NEG/2)
    {
    	unpauseAudio();
        return true;
    }
    else
    {
        return false;
    }
}

bool checkRestart ()
{
    jcoord_t coord = joy_get_coord();
    if(coord.x > JOY_MAX_POS/2)
    {
    	unpauseAudio();
        return true;
    }
    else
    {
        return false;
    }
}

void initializeRaspy()
{
    joy_init();
    initAudio();

    raspySounds[BURN] = LINE;
    raspySounds[GAME_OVER] = LOSE;
    raspySounds[MOVE_SIDEWAYS] = MOVE;
    raspySounds[TETRIS] = LEVEL;
    raspySounds[ROTATE] = ROT;

    disp_init();
    disp_clear();
    disp_update();
    playMusic(GAME, SDL_MIX_MAXVOLUME / 2);
    srand(time(NULL));
}

void raspyPlaySound(int soundIndex)
{
    playSound(raspySounds[soundIndex], SDL_MIX_MAXVOLUME);
}


void raspyDisplayClearPreDraw ()
{
	disp_clear();
}

void raspyShowScore(int score) {
    // Si el puntaje es 0, dibuja el dígito 0 y retorna
    if (score == 0) {
        // Desplaza el número de derecha a izquierda en el LED
		for (int offset_x = 16 - 6, offset_y = 8 - 4; offset_x >= -6; offset_x--) {
		    // Borra el contenido actual del buffer
		    disp_clear();

	        for (int j = 0; j < 8; j++) {
	            for (int k = 0; k < 6; k++) {
	                if ( k + offset_x >= 0 &&  k + offset_x < 16) {
	                    int x = k + offset_x;
	                    int y = j + offset_y;

	                    if (digitMatrices[0][j][k] == 1 && y >= 0 && y < 16) {
	                        dcoord_t point = {x, y};
	                        disp_write(point, D_ON);
	                    }
	                }
	                joyUpdateValues();
	                if (checkRestart()) {
	                	disp_clear();
	                	disp_update();
	                    return;
	                }
	            }
	        }
		    

		    // Actualiza el display
		    disp_update();

		    // Espera un tiempo (ajusta según sea necesario)
		    usleep(50000); // 50 milisegundos
		}
		return;
    }

    // Convierte el número en un array de dígitos
    int digits_array[6];
    for (int i = 5; i >= 0; i--) {
        digits_array[i] = score % 10;
        score /= 10;
    }

    // Encuentra el primer dígito no cero
    int firstNonZero = 0;
    while (firstNonZero < 6 && digits_array[firstNonZero] == 0) {
        firstNonZero++;
    }

    // Desplaza el número de derecha a izquierda en el LED
    for (int offset_x = 16 - 6, offset_y = 8 - 4; offset_x >= -6 - 30; offset_x--) {
        // Borra el contenido actual del buffer
        disp_clear();

        // Coloca los dígitos en el buffer con el desplazamiento actual
        for (int i = firstNonZero; i < 6; i++) {
            int x_start = (i - firstNonZero) * 6;

            for (int j = 0; j < 8; j++) {
                for (int k = 0; k < 6; k++) {
                    if (x_start + k + offset_x >= 0 && x_start + k + offset_x < 16) {
                        int x = x_start + k + offset_x;
                        int y = j + offset_y;

                        if (digitMatrices[digits_array[i]][j][k] == 1 && y >= 0 && y < 16) {
                            dcoord_t point = {x, y};
                            disp_write(point, D_ON);
                        }
                    }
                    joyUpdateValues();
                    if (checkRestart()) {
                        disp_clear();
	                	disp_update();
                        return;
                    }
                }
            }
        }

        // Actualiza el display
        disp_update();

        // Espera un tiempo (ajusta según sea necesario)
        usleep(50000); // 50 milisegundos
    }
}


void dispUpdateValues ()
{
	disp_update();
}

void destroyRaspy ()
{
	endAudio();
}

void raspyMenu(Game * game) {
    dcoord_t coord;

    // P en el 8x8 superior izquierdo
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            coord.x = j;
            coord.y = i;
            disp_write(coord, menuMatrices[0][i][j]);
        }
    }

    // Flecha hacia arriba en el 8x8 superior derecho
    for (int i = 0; i < 8; ++i) {
        for (int j = 8; j < 16; ++j) {
            coord.x = j;
            coord.y = i;
            disp_write(coord, menuMatrices[2][i][j - 8]);
        }
    }

    // Q en el 8x8 inferior izquierdo
    for (int i = 8; i < 16; ++i) {
        for (int j = 0; j < 8; ++j) {
            coord.x = j;
            coord.y = i;
            disp_write(coord, menuMatrices[1][i - 8][j]);
        }
    }

    // Flecha hacia abajo en el 8x8 inferior derecho
    for (int i = 8; i < 16; ++i) {
        for (int j = 8; j < 16; ++j) {
            coord.x = j;
            coord.y = i;
            disp_write(coord, menuMatrices[3][i - 8][j - 8]);
        }
    }

    // Actualizar la pantalla
    disp_update();
}

#endif

	

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
