/* *****************************************************************
    *                     FILE CONFIGURATION                      *
   ***************************************************************** */

/* --------------------- NECESSARY LIBRARIES --------------------- */

// Provides macros for unit testing
#include <assert.h>

// Provides input/output functionalities
#include <stdio.h>

/* ---------------------- NECESSARY HEADERS ---------------------- */

// Header for the port emulation library
#include "M68HC11.h"


/* *****************************************************************
    *                   TEST FUNCTION DEFINITIONS                 *
   ***************************************************************** */

/* ---------------------- TEST INITIALIZATION ---------------------- */

// Tests the initialization of the ports
void test_port_initialization(void)
{
    // Initialize ports
    configure_port_a(0x00);
    configure_port_b(0x00);
    write_port_a(0x00);
    write_port_b(0x00);

    // Verify that all bits are initially cleared
    assert(read_port_a() == 0x00);
    assert(read_port_b() == 0x00);

    printf("test_port_initialization passed.\n");
}

/* --------------------- TEST PIN OPERATIONS --------------------- */

// Tests setting and clearing individual bits
void test_pin_set_and_clear(void)
{
    // Clear ports
    write_port_a(0x00);

    // Set each bit and verify
    for (int i = 0; i < 8; i++)
    {
        bitSet(&PORTA, i);
        assert(bitGet(PORTA, i) == 1);
    }

    // Clear each bit and verify
    for (int i = 0; i < 8; i++)
    {
        bitClr(&PORTA, i);
        assert(bitGet(PORTA, i) == 0);
    }

    printf("test_pin_set_and_clear passed.\n");
}

// Tests toggling bits
void test_pin_toggle(void)
{
    // Clear ports
    write_port_a(0x00);

    // Toggle each bit and verify
    for (int i = 0; i < 8; i++)
    {
        bitToggle(&PORTA, i);
        assert(bitGet(PORTA, i) == 1);
        bitToggle(&PORTA, i);
        assert(bitGet(PORTA, i) == 0);
    }

    printf("test_pin_toggle passed.\n");
}

/* --------------------- TEST INVALID OPERATIONS --------------------- */

// Tests handling invalid bit numbers
void test_invalid_pin_operations(void)
{
    // Clear ports
    write_port_a(0x00);

    // Attempt to access invalid bits and verify no changes occur
    bitSet(&PORTA, 8);
    assert(read_port_a() == 0x00);

    bitClr(&PORTA, 8);
    assert(read_port_a() == 0x00);

    bitToggle(&PORTA, 8);
    assert(read_port_a() == 0x00);

    printf("test_invalid_pin_operations passed.\n");
}


/* *****************************************************************
    *                        MAIN FUNCTION                        *
   ***************************************************************** */

int main(void)
{
    // Run all tests
    test_port_initialization();
    test_pin_set_and_clear();
    test_pin_toggle();
    test_invalid_pin_operations();

    printf("All tests passed successfully.\n");

    return 0;
}
