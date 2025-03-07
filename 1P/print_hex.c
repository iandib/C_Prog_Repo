#include <stdint.h>  
#include <stdio.h>   

// Función auxiliar que imprime un dígito hexadecimal
void print_hex_digit(uint8_t digit) 
{
    if (digit < 10) 
    {
        putchar('0' + digit);
    } 
    else 
    {
        putchar('A' + (digit - 10));
    }
}

// Función que imprime un número de 16 bits en hexadecimal
void print_hex_word(uint16_t word) 
{
    // Imprime el dígito más significativo
    print_hex_digit((word >> 12) & 0xF);
    
    // Imprime el segundo dígito
    print_hex_digit((word >> 8) & 0xF);
    
    // Imprime el tercer dígito
    print_hex_digit((word >> 4) & 0xF);
    
    // Imprime el dígito menos significativo
    print_hex_digit(word & 0xF);
    
    putchar('\n');
}

int main(void) 
{
    // Ejemplo con 0xAB23
    print_hex_word(0xAB23);
    
    return 0;
}
