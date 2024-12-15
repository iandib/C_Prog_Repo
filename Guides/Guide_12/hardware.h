/* *****************************************************************
    *                    HEADER CONFIGURATION                     *
   ***************************************************************** */

// We make sure the header is only included once
#ifndef HARDWARE_H
#define HARDWARE_H

/* --------------------- NECESSARY LIBRARIES --------------------- */

// Standard Input/Output library
#include <stdio.h>

// Standard library for string manipulation
#include <string.h>

/* ---------------------- MACROS & CONSTANTS ---------------------- */

// Path to the GPIO control files
#define GPIO_PATH  "/sys/class/gpio/"

// Maximum string length
#define MAX_STR_LEN 35

/* ------------------ PUBLIC FUNCTIONS PROTOTYPES ------------------ */

// Function initializes all pins
void initializePins();

// Function releases all pins
void releasePins();

#endif // HARDWARE_H

