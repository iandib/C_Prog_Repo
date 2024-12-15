#include <stdio.h>

int main(void)
{
    char c;

    /* El bucle for inicializa 'c' con 1 y lo incrementa hasta 4
    Cada iteración del bucle ejecuta el switch para el valor actual de 'c' */
    for (c = '1'; c <= '4'; c++)
    
        switch(c) 
        { 
            // Como no hay un break entre los primeros dos casos, ambos bloques se ejecutan si 'c' es 1 o 2
            case '1': case '2': 
                printf("Caso a - %c \n", c); 
                
                // Si se elimina el primer break, el programa ejecuta el siguiente caso sin importar su condición
                break; 
                
            // Este bloque solo se ejecuta si 'c' es 3
            case '3': 
                printf("Caso b - %c \n", c); 
                
                // Si se elimina el segundo break, el programa continúa hasta el caso default
                break; 
                
            // El bloque default se ejecuta si 'c' no coincide con 1, 2 o 3 (es decir, si 'c' es 4)
            default: 
                printf("Caso c - %c \n", c); 
        }

    return 0;
}
