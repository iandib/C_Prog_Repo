#include <stdio.h>

#define TAB_FILS 8
#define TAB_COLS 8

// defino mis tipos
typedef char celda_tablero_t;
typedef celda_tablero_t fila_tablero_t[TAB_COLS];
typedef fila_tablero_t tablero_t[TAB_FILS];


void print_pieza(celda_tablero_t);


int main(void)
{
    tablero_t tablero;

    // Imprimo los tamaños de mis nuevos tipos
    printf("Tama\xA4o tablero_t %d\n", sizeof(tablero_t));
    printf("Tama\xA4o fila_tablero_t %d\n", sizeof(fila_tablero_t));
    printf("Tama\xA4o celda_tablero_t %d\n", sizeof(celda_tablero_t));

    // imprimo una celda, a través de una función
    tablero[1][3] = 't';
    printf("\n\nCelda [1][3]:\n");
    print_pieza(tablero[1][3]);

    return 0;
}


void print_pieza(celda_tablero_t pieza)
{
    switch (pieza)
    {
        case 't':
            printf("TORRE\n");
            break;

        case 'r':
            printf("REY\n");
            break;

        default:
            printf("???\n");
            break;
    }
}
