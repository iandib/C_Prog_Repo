#include <stdio.h>

int main(void)
{
    int x, *px;	  /* Definición de las variables */
    px = &x;       /* Almaceno la dirección de x en px */
    *px = 0;       /* Se le asigna el valor 0 a x
                    a través del puntero px */
    *px = *px + 3; /* Equivalente a x = x + 3 */ 
    x = *px + 1;   /* Equivalente a x = x + 1 */
    *px*=x*2;      /* Equivalente a x = x * x * 2 */

    printf("%d %d \n", x, *px); /* Imprime 2 veces x */
    return 0;
}

