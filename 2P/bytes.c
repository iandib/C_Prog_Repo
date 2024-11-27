#include <stdio.h>

// Imprimir 34 en plataforma con arquitectura de 32 bits, little-endian
int main(void)
{
    int var = 0x12345678;
    char* pbyte;

    // Apuntar al inicio de var, pero trabajando con punteros a bytes
    pbyte = (char*) &var;

    // Desplazarte un byte para apuntar al byte 0x34
    pbyte += 1;

    // Imprimir el valor del byte apuntado
    printf("%X\n", *pbyte);
    return 0;
}
