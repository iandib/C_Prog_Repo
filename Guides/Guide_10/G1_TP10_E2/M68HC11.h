/* *****************************************************************
    *                  HEADER FILE CONFIGURATION                  *
   ***************************************************************** */

// Ensure the header is included only once
#ifndef M68HC11_SIM_H
#define M68HC11_SIM_H

/* ---------------------- NECESSARY LIBRARIES ---------------------- */

// Standard library for working with integers
#include <stdint.h>

/* ---------------------- PORTS AND REGISTERS ---------------------- */

// Port A (8 bits)
static uint8_t PORTA = 0x00;

// Port B (8 bits)
static uint8_t PORTB = 0x00;

// Data Direction Register for Port A
static uint8_t DDRA = 0x00;

// Data Direction Register for Port B
static uint8_t DDRB = 0x00;

/* ------------------------ BIT OPERATIONS ------------------------ */

// Set a specific bit in a port
void bitSet(uint8_t *port, uint8_t bit);

// Clear a specific bit in a port
void bitClr(uint8_t *port, uint8_t bit);

// Toggle a specific bit in a port
void bitToggle(uint8_t *port, uint8_t bit);

// Get the value of a specific bit in a port
uint8_t bitGet(uint8_t port, uint8_t bit);

/* ----------------------- MASK OPERATIONS ----------------------- */

// Apply a mask to set bits in a port
void maskOn(uint8_t *port, uint8_t mask);

// Apply a mask to clear bits in a port
void maskOff(uint8_t *port, uint8_t mask);

// Apply a mask to toggle bits in a port
void maskToggle(uint8_t *port, uint8_t mask);

/* ----------------------- PORT OPERATIONS ----------------------- */

// Write a value to Port A
void write_port_a(uint8_t value);

// Write a value to Port B
void write_port_b(uint8_t value);

// Read the current value of Port A
uint8_t read_port_a();

// Read the current value of Port B
uint8_t read_port_b();

// Configure the direction of Port A (1 = output, 0 = input)
void configure_port_a(uint8_t direction);

// Configure the direction of Port B (1 = output, 0 = input)
void configure_port_b(uint8_t direction);

// Write a 16-bit value to Port D (Port A is the upper byte, Port B is the lower byte)
void write_port_d(uint16_t value);

// Read the 16-bit value from Port D (Port A is the upper byte, Port B is the lower byte)
uint16_t read_port_d();

#endif // M68HC11_SIM_H
