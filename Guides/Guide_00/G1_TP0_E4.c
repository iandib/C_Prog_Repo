#include <stdio.h>
// La librería math.h permite calcular pi matemáticamente
#include <math.h>

// TODO: preguntar si float no debería tener menos precisión que double --> puedo imprimir 25 dígitos con ambos

int main() {
    // Cálculo de pi (variable tipo double) usando el arco coseno
    double pi = acos(-1.0);
    
    // Cálculo de pi (variable tipo float) usando el arco coseno
    // float pi = acos(-1.0f);

    // 2 decimales
    printf("%.2f \n", pi);
    // 5 decimales
    printf("%.5f \n", pi);
    // 10 decimales
    printf("%.10f \n", pi);
    // 15 decimales
    printf("%.15f \n", pi);
    // 20 decimales
    printf("%.20f \n", pi);
    // 25 decimales
    printf("%.25f \n", pi);

    // Sin especificar decimales
    printf("%f \n", pi);

    return 0;

    /* 
    El valor por defecto de decimales con %f es 6, independientemente de 
    si se utiliza float o double.
    */
}

/*
math.h library documentation: 
https://pubs.opengroup.org/onlinepubs/9799919799/
https://en.wikibooks.org/wiki/C_Programming/math.h

*/ 
