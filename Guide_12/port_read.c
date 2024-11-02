/* *****************************************************************
    *                        INFORMATION                          *
   ***************************************************************** 
   
	* @file port_read.c
	* @brief Function to read ports and control GPIO pins based on port state
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
#include "port_read.h"


/* *****************************************************************
    *                    MANAGE PORTS FUNCTION                    *
   ***************************************************************** */

// Function to read ports and control GPIO pins based on port state
void port_read(void) 
{
	/* ------------------ LOCAL VARIABLES ------------------ */
	
	// Variable to represent the state of port A
	port portA;

	// Array of bit values from the portA structure
    uint8_t port_bits[] = {portA.b0, portA.b1, portA.b2, portA.b3, portA.b4, portA.b5, portA.b6, portA.b7};

    // File handle for each GPIO pin
	FILE *handle;
    
    // Array of file paths for each GPIO pin, indexed by port bit positions
    const char *gpio_paths[] =
	{
        "/sys/class/gpio/gpio17/value",
        "/sys/class/gpio/gpio4/value",
        "/sys/class/gpio/gpio18/value",
        "/sys/class/gpio/gpio23/value",
        "/sys/class/gpio/gpio24/value",
        "/sys/class/gpio/gpio25/value",
        "/sys/class/gpio/gpio22/value",
        "/sys/class/gpio/gpio27/value"
    };   

	/* ------------------ PINS MANAGEMENT ------------------ */
    
    // Loop through each bit and set corresponding GPIO pin value based on bit state
    for (int i = 0; i < 8; i++)
    {
        // Check the state of the current bit
        if (port_bits[i] == 1 || port_bits[i] == 0)
        {
            // Try to open the file for the current GPIO pin; 
            handle = fopen(gpio_paths[i], "w");
            if (handle == NULL)
            {
                printf("Error al abrir archivo\n");
                exit(1);
            }

            else
            {
                printf("Archivo %s abierto con exito\n", gpio_paths[i]);
            }

            // Write '1' if bit is set, '0' otherwise
            if (fputc(port_bits[i] ? '1' : '0', handle) == -1)
            {
                printf("Error al prender/apagar pin %d\n", i);
                exit(1);
            }
            else
            {
                printf("Pin %d prendido/apagado\n", i);
            }
            
            // Close the file after updating the pin
            fclose(handle);
        }
    }
}
