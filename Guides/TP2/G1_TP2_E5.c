#include <stdio.h>

/* El código sirve para aproximar e^x centrado en 0; la fórmula es más sencilla en este caso, 
pues la derivada enésima centrada en 0 es simplemente e^0 = 1 */

// Definimos el valor en el que se evalúa la serie
#define x_value 2.0

// Definimos el número de términos de la serie
#define total_terms 10

int main(void) 
{
    // Definimos e inicializamos e^x con 1 (el primer término de la serie)
    double e_x = 1.0;

    // Definimos una variable para almacenar cada término de la serie
    double term = 1.0;

    /* Calculamos la aproximación de e^x usando un bloque for que se itera hasta que 
    el número de derivada es igual al de la cantidad de términos que se quiere que tenga la serie */
    for (int deriv = 1; deriv <= total_terms; deriv++) 
    {
        // Calculamos el siguiente término de la serie
        term = term * (x_value / deriv);

        // Sumamos cada término a la aproximación de e^x
        e_x += term;
    }
    
    // Imprimimos el valor calculado de e^x
    printf("El valor aproximado de e^%.2f es: %.10f \n", x_value, e_x);

    return 0;
}


