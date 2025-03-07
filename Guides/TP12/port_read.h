/* *****************************************************************
    *                    HEADER CONFIGURATION                     *
   ***************************************************************** */

// We make sure the header is only included once
#ifndef PORT_READ_H
#define PORT_READ_H

/* --------------------- NECESSARY LIBRARIES --------------------- */

// Standard Input/Output library
#include <stdio.h>

// Standard Library for general utilities
#include <stdint.h>

// Standard Library for general utilities
#include <stdlib.h>

/* ------------------- STRUCTURES && DATA TYPES ------------------- */

// Structure to represent the state of a port
typedef struct 
{
    int b0;
    int b1;
    int b2;
    int b3;
    int b4;
    int b5;
    int b6;
    int b7;
} port;

/* ------------------ PUBLIC FUNCTIONS PROTOTYPES ------------------ */

// Function to read ports and control GPIO pins based on port state
void port_read (void);

#endif // PORT_READ_H