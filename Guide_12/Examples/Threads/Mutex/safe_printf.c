////gcc -o safe_printf safe_printf.c -lpthread

#include <stdio.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h> 
#include <stdint.h>


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

pthread_mutex_t printf_mutex;
int sync_printf(const char *format, ...);

void * thread1();
void * thread2();
void * thread3();


#define  ONE_MS    	1000	   // One mseg
#define  TIME_BASE  50         // in mseg 
#define  time_delay(x)  (x/TIME_BASE)    // x in ms , minvalue 100mseg

uint32_t delaylp=50*ONE_MS;
uint32_t last_time;
unsigned int TimerTick;

int main(void)
{

		int status;
        pthread_t tid1,tid2,tid3,tid4;
        pthread_mutex_init(&printf_mutex, NULL);
        
        printf("Start \n");

		

        pthread_create(&tid1,NULL,thread1,NULL);
        pthread_create(&tid2,NULL,thread2,NULL);
        pthread_create(&tid3,NULL,thread3,NULL);
      
        
        pthread_join(tid1,NULL);
        pthread_join(tid2,NULL);
        pthread_join(tid3,NULL);
      
        return 0;

	
}


void * thread1()  // Time base Thread
{
    while(1)
    {
               
		usleep(TIME_BASE*ONE_MS); // TIME_BASE in ms * 

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
	   	  
	        TimerTick=time_delay(100);             // 100ms 
	        sync_printf("Thread 2 r=%d\n",r++);  // Test Print
	      
	                
	    }

	}

}




void * thread3() // The APP

{
	while (1)
	{
	
				sync_printf(YELLOW_TEXT "The" " App\n" WHITE_TEXT );
				sleep(1);
	
	}
}



int sync_printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    pthread_mutex_lock(&printf_mutex);
    vprintf(format, args);
    pthread_mutex_unlock(&printf_mutex);

    va_end(args);
}
