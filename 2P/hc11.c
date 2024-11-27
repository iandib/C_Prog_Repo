#include <stdio.h>
#include <stdint.h>

typedef struct
{
    // Parte alta (8 bits más significativos en big-endian)
    uint8_t hi;

    // Parte baja (8 bits menos significativos en big-endian)
    uint8_t lo; 
} byte_t;

typedef union 
{
    // Acceso completo de 16 bits
    uint16_t word; 

    // Acceso a bytes individuales
    byte_t byte;
} reg_t;


int main(void) 
{
    // Inicializo r1 con el valor completo de 16 bits 0x1234
    reg_t r1 = {0x1234}; 

    // Inicializo r2 asignando valores a hi y lo para la arquitectura big-endian
    reg_t r2;

    // Parte alta de r2 (byte más significativo)
    r2.byte.hi = 0x56;

    // Parte baja de r2 (byte menos significativo)
    r2.byte.lo = 0x78;

    // Imprimir el registro completo r2 en hexadecimal
    printf("S1: %X\n", r2.word);

    // Imprimir la parte baja de r1 en hexadecimal
    printf("S2: %X\n", r1.byte.lo);

    // Imprimir la parte alta de r1 en hexadecimal
    printf("S3: %X\n", r1.byte.hi);

    return 0;
}
