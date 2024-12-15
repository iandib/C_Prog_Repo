/* Compara pasaje por argumento a funciones:
   int vs. array */

#include <stdio.h>

void magicInt(int);
void magicArr(int[]);

int main(void)
{
    int testInt = -5;
	int testArr[3] = {23, 24, 25};

    printf("Original:\n%d\n[%d,%d,%d]\n", testInt, testArr[0], testArr[1], testArr[2]);

	magicInt(testInt);
	magicArr(testArr);

    printf("Final:\n%d\n[%d,%d,%d]\n", testInt, testArr[0], testArr[1], testArr[2]);
	
    return 0;
}

void magicInt(int a)
{
	a += 7;
}

void magicArr(int v[])
{
	v[1] += 7;
}



