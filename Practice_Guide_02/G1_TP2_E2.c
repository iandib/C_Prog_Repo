#include <stdio.h>

int main(void) 
{
    int x = 5;

    /* El bucle while debería ejecutar el printf hasta que x sea 0
    Pero por el ';' al final de la instrucción, el while termina ahí */
    while(x > 0);
    
        // El printf se termina ejecutando fuera del bucle debido al ';' en el while
        printf("%d \n", x--);
        
    return 0;
}
