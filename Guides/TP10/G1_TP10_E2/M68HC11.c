/* *****************************************************************
    *                        INFORMATION                          *
   ***************************************************************** 
  
    --------------------- PORT D OPERATIONS ---------------------

    Port D is a 16-bit virtual port that combines Port B (lower byte) and Port A (upper byte). The following operations
    explain how it works:

    - Writing to Port D
        When writing to Port D, the lower byte (bits 0-7) is stored in Port B, and the upper byte (bits 8-15) is stored 
        in Port A. This is achieved using bitwise operations:
            write_port_b((uint8_t)(value & 0xFF));
            write_port_a((uint8_t)(value >> 8));
        Here:
            (value & 0xFF) extracts the lower 8 bits of 'value' using a mask.
            (value >> 8) shifts 'value' 8 bits to the right to extract the upper byte.

    - Reading from Port D
        When reading from Port D, the 8 bits of Port A are shifted to the left by 8 positions and combined with the 8 bits 
        of Port B using the OR operator:
            return ((uint16_t)PORTA << 8) | PORTB;
        This reconstructs the 16-bit value of Port D.

        These operations ensure that Port D behaves as a single 16-bit register, while internally using the 8-bit registers 
        Port A and Port B.

    ---------------------- PORT A/B BIT MODIFICATION ----------------------

    When writing to Port A or Port B, only the bits configured as outputs (indicated by a '1' in the direction registers 
    DDRA/DDRB) can be modified. The operation:
        PORTA = (PORTA & ~DDRA) | (value & DDRA);
    ensures this behavior. Here's how it works:
        (PORTA & ~DDRA) keeps the current values of input bits (0 in DDRA).
        (value & DDRA) extracts the output bits from 'value' (1 in DDRA).
        The result combines the unchanged input bits with the updated output bits.

    This ensures that input bits are not accidentally altered when writing to the ports, maintaining proper functionality.
*/


/* *****************************************************************
    *                     FILE CONFIGURATION                      *
   ***************************************************************** */

/* ---------------------- NECESSARY HEADERS ---------------------- */

#include "M68HC11.h"


/* *****************************************************************
    *                   OPERATIONS / FUNCTIONS                    *
   ***************************************************************** */

/* ------------------------ BIT OPERATIONS ------------------------ */

// Set a bit in a port
void bitSet(uint8_t *port, uint8_t bit)
{
    *port |= (1 << bit);
}

// Clear a bit in a port
void bitClr(uint8_t *port, uint8_t bit)
{
    *port &= ~(1 << bit);
}

// Toggle a bit in a port
void bitToggle(uint8_t *port, uint8_t bit)
{
    *port ^= (1 << bit);
}

// Get a bit value from a port
uint8_t bitGet(uint8_t port, uint8_t bit)
{
    return (port >> bit) & 1;
}

/* ----------------------- MASK OPERATIONS ----------------------- */

// Apply a mask and set bits
void maskOn(uint8_t *port, uint8_t mask)
{
    *port |= mask;
}

// Apply a mask and clear bits
void maskOff(uint8_t *port, uint8_t mask)
{
    *port &= ~mask;
}

// Apply a mask and toggle bits
void maskToggle(uint8_t *port, uint8_t mask)
{
    *port ^= mask;
}

/* ----------------------- PORT OPERATIONS ----------------------- */

// Function to write to Port A
void write_port_a(uint8_t value)
{
    // Only update bits configured as output (1 in DDRA)
    PORTA = (PORTA & ~DDRA) | (value & DDRA);
}

// Function to write to Port B
void write_port_b(uint8_t value)
{
    // Only update bits configured as output (1 in DDRB)
    PORTB = (PORTB & ~DDRB) | (value & DDRB);
}

// Function to read from Port A
uint8_t read_port_a()
{
    // Return the state of Port A
    return PORTA;
}

// Function to read from Port B
uint8_t read_port_b()
{
    // Return the state of Port B
    return PORTB;
}

// Function to configure Port A direction
void configure_port_a(uint8_t direction)
{
    DDRA = direction;
}

// Function to configure Port B direction
void configure_port_b(uint8_t direction)
{
    DDRB = direction;
}

// Function to write to Port D (16 bits: Port B is the lower byte, Port A is the upper byte)
void write_port_d(uint16_t value)
{
    // Write lower byte to Port B
    write_port_b((uint8_t)(value & 0xFF));

    // Write upper byte to Port A
    write_port_a((uint8_t)(value >> 8));
}

// Function to read from Port D (16 bits: Port B is the lower byte, Port A is the upper byte)
uint16_t read_port_d()
{
    return ((uint16_t)PORTA << 8) | PORTB;
}

