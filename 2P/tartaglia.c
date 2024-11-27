#include <stdio.h>

int matTartaglia(int i, int j)
{
    // índices inválidos
    if (i < 1 || j < 1)
    {
        return 0;
    }

    // Caso base: primera fila/columna
    if (i == 1 || j == 1)
    {
        return 1;
    }

    // Caso recursivo: disminución del grado en ambas direcciones
    return matTartaglia(i - 1, j) + matTartaglia(i, j - 1);
}
