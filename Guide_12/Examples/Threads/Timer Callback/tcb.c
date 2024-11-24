// gcc -o tcb tcb.c -lpthread

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void function(void);      //callback
unsigned int beeptime;   // time interval counter
void (*pfun)(void)=NULL;  
void register_timer_function (void (*pf)(void),unsigned int time);
unsigned int time_interval; // Event time

void * thread1()  // Time base Task
{
        while(1) {
               
		usleep(100*1000); // 100ms  

		if (beeptime)		
			beeptime--;
		else			// Time Event !!
		
		{
	          	beeptime=time_interval;	 //reload counter
	        	
	               	if(pfun!=NULL)
			   	pfun();		//call the callback
	        }
	  


        }
}


void * thread2() // Main task

{

	register_timer_function(&function,4); //register Callback (4 seg) 

	while (1) {
	
		printf("Main\n");

		sleep(1);

		}
	
}
/*************************************************************
Register CallBack function for periodic time events
Arguments : pointer to callback and time in seconds
**************************************************************/
void register_timer_function (void (*pf)(void),unsigned int time)
{

		pfun=pf;
		time_interval=time*10;

}

void function(void)
{

		printf("Function was called\n");

}


int main()  //launcher
{
        int status;
        pthread_t tid1,tid2,tid3;

        pthread_create(&tid1,NULL,thread1,NULL);
        pthread_create(&tid2,NULL,thread2,NULL);
        pthread_join(tid1,NULL);
        pthread_join(tid2,NULL);
        
        return 0;
}

