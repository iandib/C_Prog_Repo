/*
 * main.c
 *
 *  Created on: Nov 25, 2024
 */

#include "Back_End/game_logic.h"
#include "th2_display_sound.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>


sem_t s;					//This global semaphore will stop the execution of th1_gamelogic as long as the user is not playing.


int main(void)
{
	if (sem_init(&s, 0, 0) != 0)					//The semaphore is initialized with the value of 0, shared between threads
	{
	// Error: initialization failed
		return 1;
	}
	Game game;											//Main game structure is created
	void * gamep = &game;
    //FILE *leaderboard = fopen("leaderboard.txt", "ab+");		//This line amd the next one make sure that the leaderboard exists
    //fclose(leaderboard);

	pthread_t th1,th2;
	pthread_create(&th1,NULL,th1_gamelogic, gamep); 			//Thread 1 is created
	pthread_create(&th2,NULL,th2_display_sound, gamep); 		//Thread 2 is created
	pthread_join(th1,gamep);
	pthread_join(th2,gamep);
	return 0;
}

