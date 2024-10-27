#include <stdio.h>

int main(void)
{
	int numeros[3][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12}};

    //int *p2intA = &numeros[1][0];
    //int *p2intB = numeros[1];
    //int *p2intC = numeros;

    printf("%p\n", numeros);
    printf("%p\n", numeros[2]);
    printf("%p\n", &numeros[1][2]);
    printf("%p\n", numeros+1);
    printf("%p\n", numeros[2]-1);

    return 0;
}
