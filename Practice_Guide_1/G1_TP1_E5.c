#include <stdio.h>

int main(void)  
{  
    unsigned char x = 255;  
    signed char y = -1; 
    
    /* 255 en binario es ... 0000 1111 1111, por lo que al shiftearlo dos lugares a derecha
    queda ... 0000 0011 1111 que corresponde al número 63, que luego imprime */

    /* -1 en binario es ... 1111 1111 1111, por lo que al shiftearlo dos lugares a derecha
    sigue quedando ... 1111 1111 1111 e imprime el -1 */

    printf("x = %d \ny = %d \n", x>>2, y>>2);  
    
    return 0;  
}
