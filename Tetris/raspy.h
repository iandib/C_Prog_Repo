/***************************************************************************//**
  @file     +raspy.h
  @brief    +raspberrypi constants and functions
  @author   +Helou, Luchelli, Segura
 ******************************************************************************/
 
#ifndef _RASPY_H
#define _RASPY_H

/*******************************************************************************
* INCLUDE HEADER FILES
******************************************************************************/

#include "common.h"

#ifndef PC

#include "disdrv.h"  // Archivo de cabecera del display
#include "joydrv.h"
#include "gameLogic.h"
#include "libaudio.h"	// Archivo de cabecera del audio

extern int digitMatrices[10][8][6];

extern int menuMatrices[4][8][8];

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
 
 void draw_board(Game* game);
 void moveSideways (Game* game); 
 void rotate (Game* game);
 void showNext (Game* game);
 void showLevel (Game* game);
 void joyUpdateValues ();
 void dispUpdateValues ();
 bool checkPasue ();
 bool checkResume ();
 bool checkRestart ();
 void initializeRaspy ();
 void raspyDisplayClearPreDraw ();
 void draw_tetromino(Game* game);
 void clearDisp ();
 void moveTetromino (Game* game);
 bool checkQuit ();
 void raspyShowScore (int score);
 void destroyRaspy ();
 void raspyMenu(Game * game);
 void raspyPlaySound(int soundIndex);
 


 #endif
 
 #endif // _RASPY_H
