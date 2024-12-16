#include <stdio.h>
#include <stdint.h>

#define CUBE(a)  a*a*a  

int var1=10; 

int a2d[3][4] = {10, 20, 30, 40, 50, 60, 70, 80, 90};  
int (*p1)[4];  
// Alternativas:  
// int (*p)[3];  
// int (**p)[3];  
// int (*p)[3][4];  
// int (**p)[3][4];


typedef struct
{  
    uint8_t var2;  
    uint8_t var3;  
} word_t;

typedef union
{  
    uint16_t data16;  
    uint8_t data8;  
    word_t new;  
} T_data; 


void main(void)  
{  
    var1 = var1 * 1.452;  
    printf("Res: %f \n", (double)var1); 
    
    p1 = a2d;

    int a = 0x101;  
    void *p2; 
    printf("a: %X \n", a);
    p2 = &a;
    *((char *) p2) = 5;  
    printf("a: %X \n", a);
        
    int var4 = 1;  
    printf("%d \n", CUBE(var4 + var4));  

    T_data x;
    x.data16 = 0x1234;  
    x.data8 = 0xAB;  
    printf("%X %02X %02X", x.data16, x.new.var2, x.new.var3);
}