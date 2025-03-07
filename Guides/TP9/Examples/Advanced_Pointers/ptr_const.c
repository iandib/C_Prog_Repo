#include <stdio.h>

int main(void)
{
  char *p = "Hola";
  //const char *p = "Hola";
  //char p[] = "Hola";
  
  
  printf("%c\n", p[2]);
  printf("%s\n", p);

  p[2] = 'L';
  printf("%s\n", p);

  return 0;
}



















#if 0




void swap(int*, int*);

int main(void)
{
  int izq = 9, der = 5;

  printf("izq: %d, der: %d\n", izq, der);
  swap(&izq, &der);
  printf("izq: %d, der: %d\n", izq, der);

  return 0;
}

void swap(int *a, int *b)
{
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;
}






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

#endif






