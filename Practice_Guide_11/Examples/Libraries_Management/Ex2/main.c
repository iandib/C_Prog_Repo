#include <stdio.h>
#include "valabs.h"
#include "valinv.h"

/* 1- create separate objects
 * gcc -c valabs.c    // create valabs.o
 * gcc -c valinv.c    // create valinv.o
 * 
 * 2- Create Library / Add or replace modules to existing library
 * 
 *     AR switches   Replace -r Verbose -v Update time stamps -U Replace if newer -u
 * 
 * 2a- First time
 *   - (Create empty library) ar -v -U -u -r libmath.a 
 *   - (create and add one module)  ar -v -U -u -r libmath.a valinv.o
 *   - (create and add several modules)  ar -v -U -u -r libmath.a valinv.o valabs.o 
 * 
 * 2b- If library already exists 
 *   
 *     Replace -r Verbose -v Update time stamps -U Replace if newer -u
 * 	    
 *     ar -v -U -u -r libmath.a valinv.o

 * 
 * 3- Get library info:  ar -v -t libmath.a
 * 4- Delete one module: ar -v -d libmath.a valinv.o
 * 
 * ar Alone prints help 
 * 
 * 
 * Compile main 
 * 
 * gcc main.c libmath.a -o main
 * 
 * gcc main.c -L. -lmath -o main   // L. library path: this directory
 * 
 * 
 *  */



int main (void)
{
   	int n=-3;
   	
   	printf("Valor Actual: %d\n",n);
    printf("Valor Absoluto: %d\n",valabs(n));
    printf("Valor Inverso: %d\n", valinv(n));
	return 0;
}
