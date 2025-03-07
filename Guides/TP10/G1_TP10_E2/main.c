/* *****************************************************************
    *                     FILE CONFIGURATION                      *
   ***************************************************************** */

/* --------------------- NECESSARY LIBRARIES --------------------- */

// Standard input-output library for printing and reading characters
#include <stdio.h>

/* --------------------- NECESSARY HEADERS ----------------------- */

// Header for port operations and bit manipulation
#include "M68HC11.h"


/* *****************************************************************
    *                        MAIN FUNCTION                        *
   ***************************************************************** */

int main()
{
    /* -------------------- INITIALIZATION -------------------- */

    // Set all bits of Port A as output (for the 8 LEDs)
    configure_port_a(0xFF);

    // Initialize Port A to all LEDs off
    write_port_a(0x00);

    // Variable to store user input
    char user_input;

    // Display instructions for the user
    printf("LED Control Program:\n");
    printf("  Enter 0-7 to toggle a specific LED. \n");
    printf("  Enter 't' to toggle all LEDs. \n");
    printf("  Enter 'c' to turn all LEDs off. \n");
    printf("  Enter 's' to turn all LEDs on. \n");
    printf("  Enter 'e' to exit the program. \n");

    /* --------------------- UPDATE LOOP --------------------- */

    // Variable to control the loop
    int exit_program = 0;

    while (!exit_program)
    {
        // Prompt the user
        printf("Enter command: ");

        // Read a single character from the user
        user_input = getchar();

        // Consume any extra input (like newlines or spaces) left in the buffer
        while (getchar() != '\n');

        // Process user input
        if (user_input >= '0' && user_input <= '7')
        {
            // Convert character to LED index (0-7)
            uint8_t led_index = user_input - '0';

            // Toggle the specified LED
            bitToggle(&PORTA, led_index);

            // Display the updated state of LEDs
            printf("PORTA: 0x%02X (LED %d toggled) \n", PORTA, led_index);
        }

        else if (user_input == 't')
        {
            // Toggle all LEDs
            maskToggle(&PORTA, 0xFF);

            // Display the updated state of LEDs
            printf("PORTA: 0x%02X (All LEDs toggled) \n", PORTA);
        }

        else if (user_input == 'c')
        {
            // Turn all LEDs off
            write_port_a(0x00);

            // Display the updated state of LEDs
            printf("PORTA: 0x%02X (All LEDs off) \n", PORTA);
        }

        else if (user_input == 's')
        {
            // Turn all LEDs on
            write_port_a(0xFF);

            // Display the updated state of LEDs
            printf("PORTA: 0x%02X (All LEDs on) \n", PORTA);
        }

        else if (user_input == 'e')
        {
            // Exit the program
            printf("Exiting program. \n");

            // Set the flag to exit the loop
            exit_program = 1;  
        }

        else
        {
            // Invalid input
            printf("Invalid command. Please try again. \n");
        }
    }

    return 0;
}
