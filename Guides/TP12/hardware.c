/* *****************************************************************
    *                        INFORMATION                          *
   ***************************************************************** 
   
	* @file hardware.c
	* @brief Hardware control functions for Raspberry Pi GPIO
	* @version 2.0
	* @date 2024-11-02
	* @compiler GCC
	* @editor VSCode && Linux
	* @OS Raspberry Pi OS
*/


/* *****************************************************************
    *                     FILE CONFIGURATION                      *
   ***************************************************************** */

/* ---------------------- NECESSARY HEADERS ------------------------ */

// Header corresponding to this file
#include "hardware.h"

/* ----------------- PRIVATE FUNCTIONS PROTOTYPES ----------------- */

// Function creates and opens a GPIO control file path
static FILE* openGpioFile(int pin, const char *action);

// Function exports a specified GPIO pin
static void exportPin(int pin);

// Function sets the direction of a specified GPIO pin
static void setPinDirection(int pin, const char *direction);

// Function sets the active-low configuration of a specified GPIO pin
static void setPinActiveLow(int pin, const char *activeLow);

// Function unexports a specified GPIO pin
static void unexportPin(int pin);

// Function prints an error message specifying the pin and action
static void printError(const char *errorMsg, int pin);

// Function exports all defined GPIO pins
static void exportAllPins();

// Function sets the direction of all GPIO pins as output
static void setAllPinsOutput();

// Function sets all GPIO pins to active high
static void setAllPinsActiveHigh();


/* *****************************************************************
    *                      PUBLIC FUNCTIONS                       *
   ***************************************************************** */

// Function initializes all pins
void initializePins()
{
    exportAllPins();
    setAllPinsOutput();
    setAllPinsActiveHigh();
}

// Function releases all pins
void releasePins()
{
    unexportPin(17);
    unexportPin(4);
    unexportPin(18);
    unexportPin(23);
    unexportPin(24);
    unexportPin(25);
    unexportPin(22);
    unexportPin(27);
}


/* *****************************************************************
    *                      PRIVATE FUNCTIONS                      *
   ***************************************************************** */

// Function creates and opens a GPIO control file path
static FILE* openGpioFile(int pin, const char *action)
{
    char filePath[MAX_STR_LEN] = {0};
    snprintf(filePath, MAX_STR_LEN, "%s%s", GPIO_PATH, action);

    // Try to open the GPIO control file
    FILE *filePointer = fopen(filePath, "w");

	// If the file pointer is NULL, print an error message
    if (!filePointer)
    {
        printError(action, pin);
    }

	// Return the file pointer
    return filePointer;
}

// Function exports a specified GPIO pin
static void exportPin(int pin)
{
    // Try to open the export file
	FILE *filePointer = openGpioFile(pin, "export");

    // If the file opens successfully, write the pin number to the file and close it
    if (filePointer)
    {
        fprintf(filePointer, "%d", pin);
        fclose(filePointer);
    }
}

// Function sets the direction of a specified GPIO pin
static void setPinDirection(int pin, const char *direction)
{
    // Create the file path for the direction file
	char filePath[MAX_STR_LEN] = {0};

	// Write the file path to the buffer
    snprintf(filePath, MAX_STR_LEN, "%sgpio%d/direction", GPIO_PATH, pin);

    // Try to open the file
	FILE *filePointer = fopen(filePath, "w");

	// If the file pointer is NULL, print an error message
    if (!filePointer)
    {
        printError("setting direction on", pin);
    }

	// Otherwise, write the direction to the file and close it
    else
    {
        fputs(direction, filePointer);
        fclose(filePointer);
    }
}

// Function sets the active-low configuration of a specified GPIO pin
static void setPinActiveLow(int pin, const char *activeLow)
{
    // Create the file path for the active low file
	char filePath[MAX_STR_LEN] = {0};

	// Write the file path to the buffer
    snprintf(filePath, MAX_STR_LEN, "%sgpio%d/active_low", GPIO_PATH, pin);

	// Try to open the file for writing
    FILE *filePointer = fopen(filePath, "w");

	// If the file pointer is NULL, print an error message
    if (!filePointer)
    {
        printError("setting active low on", pin);
    }

	// Otherwise, write the active low value to the file and close it
    else
    {
        fputs(activeLow, filePointer);
        fclose(filePointer);
    }
}

// Function unexports a specified GPIO pin
static void unexportPin(int pin)
{
    // Try to open the unexport file
	FILE *filePointer = openGpioFile(pin, "unexport");

    // If the file opens successfully, write the pin number to the file and close it
    if (filePointer)
    {
        fprintf(filePointer, "%d", pin);
        fclose(filePointer);
    }
}

// Function prints an error message specifying the pin and action
static void printError(const char *errorMsg, int pin)
{
    printf("Error %s pin %d\n", errorMsg, pin);
}

// Function exports all defined GPIO pins
static void exportAllPins()
{
    exportPin(17);
    exportPin(4);
    exportPin(18);
    exportPin(23);
    exportPin(24);
    exportPin(25);
    exportPin(22);
    exportPin(27);
}

// Function sets the direction of all GPIO pins as output
static void setAllPinsOutput()
{
    setPinDirection(17, "out");
    setPinDirection(4, "out");
    setPinDirection(18, "out");
    setPinDirection(23, "out");
    setPinDirection(24, "out");
    setPinDirection(25, "out");
    setPinDirection(22, "out");
    setPinDirection(27, "out");
}

// Function sets all GPIO pins to active high
static void setAllPinsActiveHigh()
{
    setPinActiveLow(17, "0");
    setPinActiveLow(4, "0");
    setPinActiveLow(18, "0");
    setPinActiveLow(23, "0");
    setPinActiveLow(24, "0");
    setPinActiveLow(25, "0");
    setPinActiveLow(22, "0");
    setPinActiveLow(27, "0");
}
