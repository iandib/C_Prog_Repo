/* TEST OF SEMAPHORE ON THREADS */

//Compile   gcc sem1.c -o sem1 -lpthread


#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


#define  ONE_MS    		1000	   // One mseg
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
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h> 

// gcc -o th_ex1 th_ex1.c -lpthread

char answer[1024];
sem_t len1,len2;

void * read1()
{
        while(1){
                printf("\n\nEnter a string:   ");
                fgets(answer, sizeof (answer), stdin);
                sem_post(&len1);
                sem_wait(&len2);          // es necesario ?? (Justificar)    
                
        }
}

void * write1()
{
        while(1){
                sem_wait(&len1);
                printf("\nThe string entered is :");
                printf("====> " GREEN_TEXT "%s" WHITE_TEXT "\n",answer);
                sem_post(&len2);
        }

}

int main()
{
        int status;
        pthread_t tr, tw;

		if ( sem_init(&len1, 0, 0) != 0 )
		{
			// Error: initialization failed
		}

		if ( sem_init(&len2, 0, 0) != 0 )
		{
			// Error: initialization failed
		}


        pthread_create(&tr,NULL,read1,NULL);
        pthread_create(&tw,NULL,write1,NULL);

        pthread_join(tr,NULL);
        pthread_join(tw,NULL);
        return 0;
}
