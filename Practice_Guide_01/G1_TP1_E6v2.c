#include <stdio.h>

// Versión alternativa con ciclos if-else

/* 
Definimos las siguientes máscaras con el objetivo de analizar el estado de los bits indicados en el enunciado:
- MASK1 para verificar que los bits 1 y 5 estén encendidos (0x22 corresponde a 0010 0010b).
- MASK2 para verificar que los bits 2 y 6 estén apagados (0x44 corresponde a 0100 0100b).
*/

#define MASK1 0x22
#define MASK2 0x44

int main (void){
    
    // Inicializamos la variable que representa el puerto A del 68HC11
    int porta = 56;

    /* 
    El programa sigue esta lógica:
    - Primero, verifica si los bits 1 y 5 están encendidos utilizando MASK1. Si esto es verdadero, se imprime 1.
    - Si los bits 1 y 5 no están encendidos, el programa verifica si los bits 2 y 6 están apagados utilizando MASK2.
    - Si los bits 2 y 6 están apagados, se imprime 1; si no, se imprime 0.
    */
    
    if ((porta & MASK1) == MASK1) {
        // Los bits 1 y 5 están encendidos
        printf("1 n");
    } else if ((porta & MASK2) != MASK2) {
        // Los bits 2 y 6 están apagados
        printf("1 \n");
    } else {
        // Ninguna de las condiciones anteriores es verdadera
        printf("0 \n");
    }

    return 0;
}