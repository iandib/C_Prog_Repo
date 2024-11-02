/* *****************************************************************
    *                        INFORMATION                          *
   ***************************************************************** 
   
    * @file main.c
    * @brief LED Control Program for Raspberry Pi GPIO
    * @version 2.0
    * @date 2024-11-02
    * @compiler GCC
    * @editor VSCode && Linux
    * @OS Raspberry Pi OS
*/


/* *****************************************************************
    *                     FILE CONFIGURATION                      *
   ***************************************************************** */

/* --------------------- NECESSARY LIBRARIES --------------------- */

// Standard Input/Output library
#include <stdio.h>

// Standard library for general utilities
#include <stdlib.h>

/* ---------------------- NECESSARY HEADERS ------------------------ */

// Header for GPIO pin initialization
#include "hardware.h"

// Header for port read function
#include "port_read.h"


/* ---------------------- EXTERN VARIABLES ------------------------- */

// External port variable to control LED states
extern port portA;


/* *****************************************************************
    *                      MAIN FUNCTION                          *
   ***************************************************************** */

// Function to control LEDs based on user input
int main(void)
{
    /* ------------------ LOCAL VARIABLES ------------------ */

    // Character for storing user input
    char user_char;

    // Index for iterating through LEDs
    int index;

    // Pointer to each LED bit in portA for easier manipulation
    unsigned char* led_ptr = (unsigned char*)&portA;

    /* ------------------ INITIALIZATION ------------------ */

    // Initialize GPIO pins for LED control
    initPins();

    // Set all LEDs to OFF (0) initially
    for(int i = 0; i < 8; i++)
    {
        led_ptr[i] = 0;
    }

    /* ------------------ USER INPUT LOOP ------------------ */
    
    // Loop to process user commands until 'q' or 'Q' is entered
    while((user_char = getchar()) != 'q' && user_char != 'Q')
    {
        // Print the character input by the user
        printf("%c\n", user_char);

        // Check if the input is a number between '0' and '7'
        if(user_char >= '0' && user_char <= '7')
        {
            // Set corresponding LED bit to ON
            led_ptr[user_char - '0'] = 1;
        }

        else if(user_char == 't' || user_char == 'T')
        {
            // Toggle all LEDs
            for(index = 0; index < 8; index++)
            {
                led_ptr[index] = led_ptr[index] ? 0 : 1;
            }
        }

        else if(user_char == 's' || user_char == 'S')
        {
            // Turn all LEDs ON
            for(index = 0; index < 8; index++)
            {
                led_ptr[index] = 1;
            }
        }

        else if(user_char == 'c' || user_char == 'C')
        {
            // Turn all LEDs OFF
            for(index = 0; index < 8; index++)
            {
                led_ptr[index] = 0;
            }
        }
        
        // Update LED states on the hardware
        port_read();

        // Clear extra characters in input buffer
        while((user_char = getchar()) != '\n');
    }  

    // De-initialize GPIO pins after program exit
    endPins();
    
    // Return 0 to indicate successful program completion
    return 0;
}
