#include <stdio.h>

int main (void){
    
    // Inicializamos la variable con el número al que aplicaremos las funciones
    double x = -143.5;

    // La función techo devuelve el mínimo número entero no inferior (mayor o igual) a x
    double ceiling = (x > (int)x) ? ((int)x + 1) : (int)x;
    printf("Techo de x: %f \n", ceiling);

    // La función piso devuelve el máximo número entero no superior (menor o igual) a x
    double floor = (x >= (int)x) ? (int)x : ((int)x - 1);
    printf("Piso de x: %f \n", floor);

    // La función redondeo asigna a x el número entero más próximo, redondeando sus decimales
    double rounding = (x >= 0) ? ((x - (int)x) >= 0.5 ? ((int)x + 1) : (int)x)
                                : ((x - (int)x) <= -0.5 ? ((int)x - 1) : (int)x);
    printf("Redondeo de x: %f \n", rounding);

    // La función truncamiento devuelve la parte entera de x, truncando sus decimales
    double truncation = (int)x;
    printf("Truncamiento de x: %f \n", truncation);

    // La función módulo devuelve el valor absoluto de x 
    double module = (x < 0) ? (-x) : x;
    printf("Modulo de x: %f \n", module);

    return 0;
}

// Bibliografía: https://es.wikipedia.org/wiki/Funciones_de_parte_entera


// El error en la sintaxis original fue no haber evaluado la condición de igualdad en las función piso, double floor = x > (int)x
