#include <stdint.h>  
#include <stdio.h>   

// Función que imprime el número en formato binario
void print_binary(uint16_t number) 
{
    // Imprime "Number in binary is: "
    char msg[] = "Number in binary is: ";
    
    for (int i = 0; msg[i] != '\0'; i++) 
    {
        putchar(msg[i]);
    }
    
    // Recorre los bits desde el más significativo
    for (int i = 15; i >= 0; i--) 
    {
        if (number & (1 << i)) 
        {
            putchar('1');
        }
        else 
        {
            putchar('0');
        }
        
        // Añade un espacio cada 4 bits
        if (i % 4 == 0 && i != 0) 
        {
            putchar(' ');
        }
    }
    
    putchar('\n');
}

int main(void) 
{
    // Test Number 1
    uint16_t number = 0b01110001;  
    print_binary(number);
    
    // Test Number 2
    number = 0xABCD;               
    print_binary(number);
    
    // Test Number 3
    number = 100;                  
    print_binary(number);
    
    return 0;
}
