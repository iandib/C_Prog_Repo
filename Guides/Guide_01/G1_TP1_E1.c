#include <stdio.h>  
 
int main(void)  
{

    int a = 10;  
    printf("%d",a);

    /* El programa imprime 1010, pues no se guarda a+1 en a.
    La sintaxis correcta, para imprimir 1011, sería a+=1 */
    a+1;  
    printf("%d",a); 
  
    return 0;  
}
