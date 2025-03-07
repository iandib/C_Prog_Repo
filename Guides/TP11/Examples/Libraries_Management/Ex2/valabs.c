#include <stdio.h>
#include "valabs.h"

/*
 * gcc -c valabs.c    // create valabs.o
 * 
 * 
 *
 *  */
 

int valabs(int a)
{
 return (a>0? a : (-a));
}
