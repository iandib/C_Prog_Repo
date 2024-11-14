#include <stdio.h>

int main(void)
{
  int x=5,y=5;
 
  printf("Valores iniciales de x e y:\n");
  printf("x=%d, y=%d \n",x,y);

  printf("Antes de la invocacion:\n");
  printf("x-- vale: %d, --y vale: %d \n",x--,--y);
  printf("Despues de la invocacion:\n");
  printf("x vale: %d, y vale: %d \n",x,y);

  return 0;
}
