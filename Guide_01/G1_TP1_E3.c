#include <stdio.h>  
 
int main (void) 
{      
    double half = 1/2; 
    int x = 5, y = 2;  
    double d = x/y;
 
    /* El programa imprime 0.0 y 2.0 en ambos casos debido a que ambos operandos son números enteros, 
    tal que el resultado siempre será un número entero aunque se guarde como punto flotante */
    printf("%f \n", half); 
    printf("%f \n", d);

    /* Para obtener el resultado esperado, se debe guardar 1/2 como 0.5:
    double half = 0.5;
    printf("%f \n", half);
    */
    
    /* Y se debe guardar x e y como punto flotante:
    double x = 5, y = 2;
    double d = x/y;
    printf("%f \n", d);
    */
  
    return 0;   
}
