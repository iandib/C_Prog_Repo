/*
 * main.c
 *
 *  Created on: Nov 25, 2024
 *      Author: juani
 */

#include "th1_gamelogic.h"
#include "th2_display_sound.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t s;


int main(void)
{
	if (sem_init(&s, 1, 1) != 0)
	{
	// Error: initialization failed
	}
	Game game;
	void * gamep = &game;
    FILE *leaderboard = fopen("leaderboard.txt", "ab+");		//Opens the file keeping its content or creates one with the name
    fclose(leaderboard);

	pthread_t th1,th2;
	pthread_create(&th1,NULL,th1_gamelogic, gamep); // create thread1
	pthread_create(&th2,NULL,th2_display_sound, gamep); // create thread2
	pthread_join(th1,gamep);
	pthread_join(th2,gamep);
	return 0;
}

