#include<stdio.h>

int main() {
    int variable = 16706;
    
    // El número 16706 en binario es 100000101000010, su byte menos significativo es 01000010
    
    /* Al imprimirlo con %c, se hace un casteo implícito, quedando el byte menos significativo
    (66 en base decimal), que en la tabla ASCII corresponde al caracter B */
    printf("%c \n", variable);
    
    // Al imprimirlo con %x, el número completo se transforma a hexadecimal, quedando 4142
    printf("%x \n", variable);
    
    return 0;
}