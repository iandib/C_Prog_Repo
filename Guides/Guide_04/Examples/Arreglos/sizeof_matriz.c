#include <stdio.h>

int main(void)
{
    int matriz[3][5];

    printf("sizeof(matriz): %d\n", (int)sizeof(matriz)); // tamaño de la matriz 
	printf("sizeof(matriz[1]): %d\n", (int)sizeof(matriz[1])); // tañamo de la fila
	printf("sizeof(matriz[1][2]): %d\n", (int)sizeof(matriz[1][2])); // tamaño del elemento
	
    return 0;
}
