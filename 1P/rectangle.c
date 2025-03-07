#include <stdio.h>

// Defino las dimensiones del rectángulo
#define N 4
#define M 8

void print_rectangle(unsigned char n, unsigned char m)
{
    // Defino una variable para guardar el número de filas
    unsigned int row;

    // Defino una variable para guardar el número de columnas
    unsigned int col;

    // Reviso que las dimensiones sean válidas
    if (n <= 0 || m <= 0)
    {
        printf("Error. Invalid dimensions.");
    }

    else
    {
        // Recorro todas las filas, desde la 1 hasta la n
        for (row = 1; row <= n; row++)
        {
            // Recorro todas las columnas, desde la 1 hasta la m
            for (col = 1; col <= m; col++)
            {
                // Si estamos en los bordes del rectángulo, imprimo '*'
                if (col == 1 || col == m || row == 1 || row == n)
                {
                    printf("*");
                }

                // En cualquier otra posición, imprimo ' '
                else
                {
                    printf(" ");
                }
            }

            // Salto de línea después de imprimir una fila completa
            printf("\n");
        }
    }

    // La función no retorna nada
    return;
}

int main(void)
{
    // Llamo a la función print_rectangle con las dimensiones M y N
    print_rectangle(N, M); 
}