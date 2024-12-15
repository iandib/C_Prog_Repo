#include<stdio.h>

int main() {
    int constante = 12;
    
    printf("%s \t %s \t %s \n", "Decimal", "Octal", "Hexadecimal");
    
    // Usando %x las letras a-f correspondientes a hexadecimal se imprimen minúsculas
    printf("%d \t %o \t %x \n", constante, constante, constante);
    
    // Usando %X las letras A-F correspondientes a hexadecimal se imprimen mayúsculas
    printf("%d \t %o \t %X \n", constante, constante, constante);
    
    return 0;
}