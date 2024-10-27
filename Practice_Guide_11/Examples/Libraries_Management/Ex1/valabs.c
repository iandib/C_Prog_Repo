#include <stdio.h>
#include "valabs.h"

/*
 * gcc -c valabs.c    // create valabs.o
 * 
 * Suppose main.c is the user of valabs()
 * 
 * gcc main.c valabs.o -o main
 *
 * 
 * */
 





int valabs(int a)
{
 return (a>0? a : (-a));
}
