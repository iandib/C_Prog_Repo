/*
 * th1_gamelogic.h
 *
 *  Created on: Nov 25, 2024
 *      Author: juani
 */

#ifndef TH1_GAMELOGIC_H_
#define TH1_GAMELOGIC_H_
#include "common.h"


void initializeGame(Game* game);
void * th1_gamelogic(void* gamep);
void generateNewTetromino(Game* game);

#endif /* TH1_GAMELOGIC_H_ */
