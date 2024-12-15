#include <stdio.h>

int main (void)
{
    // Establezco un array para cada tipo de dato
    int Legajo [] = {65462, 65139, 65234, 63162};
    char Nombre [][24] = {"Ian", "Bautista", "Agustin", "Tomas"};
    char Apellido [][24] = {"Dib", "Allegrini", "Rizzuto", "Luchelli"};

    // Imprimo el encabezado de cada columna
    printf("%s \t %s \t %s \n", "Legajo", "Nombre", "Apellido");
    
    /* Defino ciclo que imprime todos los datos guardados en el array, debajo 
    de las columnas correspondientes */
    for (int i=0; i<4; i++){
        printf("%d \t %s \t %s \n", Legajo[i], Nombre[i], Apellido[i]);
    }
    
    return 0;
}