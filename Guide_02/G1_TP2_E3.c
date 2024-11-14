#include <stdio.h>

// Definimos la constante TEMPER con el valor de la temperatura
#define TEMPER 25

int main(void) 
{
    // Inicializamos la variable temp con el valor de TEMPER
    int temp = TEMPER;  

    // Los condicionales verifican el rango en el que se encuentra la variable temp

    if (temp >= 30 && temp < 90)
        printf("Alta \n");

    else if (temp >= 15 && temp < 30)
        printf("Media \n");

    else if (temp >= 0 && temp < 15)
        printf("Baja \n");

    else
        printf("Caso extremo \n");

    return 0;
}

