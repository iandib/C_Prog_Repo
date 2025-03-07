#include <stdio.h>

int main(void) {
    int c, contador = 0;
    int hubo_caracter = 0;  // Bandera para saber si hubo al menos un carácter

    // Lee los caracteres de la entrada estándar hasta EOF y cuenta los saltos de línea
    while ((c = getchar()) != EOF) {
        hubo_caracter = 1;  // Marcamos que hemos leído al menos un carácter
        if (c == '\n') {
            contador++;
        }
    }

    // Si hubo caracteres y no terminó con '\n', sumamos una línea más
    if (hubo_caracter && c != '\n') {
        contador++;
    }

    // Imprime la cantidad de líneas
    printf("El archivo tiene %d renglones.\n", contador);

    return 0;
}
