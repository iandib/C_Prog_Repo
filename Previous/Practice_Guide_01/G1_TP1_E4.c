#include <stdio.h>

int main (void)  
{  
    int x = 100, y = 50;
    
    // Imprime 100
    printf ("%d \n", x);

    // Imprime 100 y guarda 101 en x
    printf ("%d \n", x++); 

    // Guarda 100 en x y lo imprime
    printf ("%d \n", --x); 

    // Imprime 100 y guarda 99 en x
    printf ("%d \n", x--); 

    // Guarda 100 en x y lo imprime
    printf ("%d \n", ++x);  
    

    // 100 en binario es ... 0000 0110 0100, por lo que en hexadecimal es 64

    // Imprime 64
    printf ("%X \n", x);

    /* (0xF4 == 0) queda 0 por ser falso y (x & 0) queda 0 por no haber dos bits encendidos en la misma posición 
    y eso es lo que imprime */
    printf ("%X \n", x & 0xF4 == 0);  

    /* (x == 0xF4) queda 0 por ser falso y (0 & 0xFF) queda 0 por no haber dos bits encendidos en la misma posición
    y eso es lo que imprime */
    printf ("%X \n", x == 0xF4 & 0xFF);

    // (x > 2) queda 1 y (1 && 0xF4) queda 1 dado que ambos datos son verdaderos y eso es lo que imprime
    printf ("%X \n", x>2 && 0xF4);

    // 32%9 queda 5 y 5%4 queda 1 y eso imprime
    printf ("%X \n", (32 % 9 % 4));

    // (x > 3) queda 1, (x > 5) queda 1 y (1 && 1) queda 1 dado que ambos datos son verdaderos y eso es lo que imprime
    printf ("%d \n", x>3 && x>5);

    /*(x > 3) queda 1, (x > 5) queda 1, (1 || 1) queda 1 dado que ambos datos son verdaderos y eso es lo que imprime;
    X queda en 100 pues como la primera evaluación || es verdadera, deja de leer en ese punto */ 
    printf ("%d \n", x>3 || x>5 || x++);
    
    // Imprime 101
    printf ("%d \n", x);

    /* (x > 3) queda 1, (x > 520) queda 0, (1 && 0) queda 0 dado que  toma 0 como un falso, finalmente (0 || x) queda 0 
    y eso es lo que imprime; X queda en 100 decimal pues como la segunda evaluación && es falsa, deja de leer en ese punto */
    printf ("%d \n", x>3 && x>520 && x++);
    
    //Imprime 100
    printf ("%d \n", x);

    // Guarda 100+50 en y y lo imprime
    printf ("%d \n", y += x); 

    // Guarda 150*100 en y y lo imprime
    printf ("%d \n", y *= x);  
    return 0;  
}
