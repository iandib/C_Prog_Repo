#include <stdio.h>

/* Evaluar lo que hace el programa,
   después ejecutarlo con GDB */

int main(void)
{
	int arr[5];
	int ind = 1;
	
	arr[0] = 5;
	arr[ind+1] = -6;
	arr[4] = 7;
	arr[ind++] = 1;
	arr[++ind] = -3;
	(++arr)[2];

	for (ind=0 ; ind<5 ; ind++)
	{
		printf("arr[%d]: %d\n", ind, arr[ind]);
	}
	
	return 0;
}

