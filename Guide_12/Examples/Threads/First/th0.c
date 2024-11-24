/* TEST OF THREADS */

//Compile  gcc -o th2 th2.c -lpthread

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


#define  ONE_MS    	1000	   // One mseg
#define  time_delay(x)  (x/100)    // x in ms , minvalue 100mseg



// ============ Colored Text ===========

#define BLACK_TEXT		   "\e[30;1m"
#define RED_TEXT		   "\e[31;1m"
#define GREEN_TEXT 		   "\e[32;1m"
#define YELLOW_TEXT 	   "\e[33;1m"
#define BLUE_TEXT 		   "\e[34;1m"
#define MAGENTA_TEXT 	   "\e[35;1m"
#define CYAN_TEXT 	   	   "\e[36;1m"
#define WHITE_TEXT 		   "\e[37m"

// ============ Colored Text End ===========

	
//http://linuxprograms.wordpress.com/2007/12/29/threads-programming-in-linux-examples/

unsigned int TimerTick;


void * thread1()  // Time base Thread
{
    while(1)
    {
               
		usleep(100*ONE_MS); // 100ms * 

		if (TimerTick)
			TimerTick--;
	
    }
}

void * thread2() // Periodic Task Thread

{
	static int r=0;
	
	while (1) 
	{

		if (!TimerTick)			// Wait for Thread1
		{
	   	  
	        TimerTick=time_delay(500);       // 500ms 
	        printf("Thread 2 r=%d\n",r++);  // Call SPI
	                
	    }

	}

}




void * thread3() // The APP

{
	while (1)
	{
	
				printf(RED_TEXT "The" " App\n" WHITE_TEXT );
				sleep(1);
	
	}
}


int main()
{
        int status;
        pthread_t tid1,tid2,tid3;
        srand(time(NULL));

        pthread_create(&tid1,NULL,thread1,NULL);
        pthread_create(&tid2,NULL,thread2,NULL);
        pthread_create(&tid3,NULL,thread3,NULL);
        pthread_join(tid1,NULL);
        pthread_join(tid2,NULL);
        pthread_join(tid3,NULL);
        return 0;
}

