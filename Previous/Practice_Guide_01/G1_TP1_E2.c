#include <stdio.h>  
 
int main(void)  
{  
    int x = 5;  
    
    /* Al usara el operador de asignación `=` en lugar del operador de comparación `==`, el valor de x 
    se modifica según el resultado del operador ternario */
    printf("Is x equal to 6: %c\n", x = 6 ? 'Y' : 'N');

    printf("New x value: %d", x);

    /* Cualquier valor diferente de 0 es considerado verdadero en C, por lo que el operador ternario selecciona 
    'Y' y lo asigna a x, obteniendo así su valor en ASCII (89).
    Si se hubiera inicializado x = 0, entonces x recibiría el valor 'N' (78 en ASCII). */

    return 0; 
}
