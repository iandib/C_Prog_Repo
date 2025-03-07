#include <stdio.h>
#include <stdint.h>

//========================================================================
typedef struct
{
    uint16_t word;   // (2 Bytes)
} WORD_REG;

typedef struct
{
    uint8_t lo; // (2 bytes)
    uint8_t hi; // OJO con el orden!!!!!! lo/hi
} BYTE_REG;

typedef struct
{
    uint16_t b0  :1 ; // (16 bits)
    uint16_t b1  :1 ; // OJO con el orden!!!!!! empieza en 0, termina en 15
    uint16_t b2  :1 ;
    uint16_t b3  :1 ;
    uint16_t b4  :1 ;
    uint16_t b5  :1 ;
    uint16_t b6  :1 ;
    uint16_t b7  :1 ;
    uint16_t b8  :1 ;
    uint16_t b9  :1 ;
    uint16_t b10 :1 ;
    uint16_t b11 :1 ;
    uint16_t b12 :1 ;
    uint16_t b13 :1 ;
    uint16_t b14 :1 ;
    uint16_t b15 :1 ;
} BIT_REG;

typedef union        // En este caso 'w' es del mismo tama¤o que 'b'
{
	WORD_REG  w;    // word (2 bytes)
	BYTE_REG  by;   // lo(1 byte),hi(1byte) (2 bytes)
	BIT_REG   bi;   // 16 bits
} MY_REG;


//========================================================================
void print_reg(MY_REG, char);


//========================================================================
int main(void)
{
    MY_REG reg1;
    char caso_cnt = 'A';

	reg1.by.hi = 0x12;   // hi =0x12
	reg1.by.lo = 0x34;   // lo= 0x34
	print_reg(reg1, caso_cnt++);

	reg1.w.word = 0xABCD;   // word = 0xABCD
	print_reg(reg1, caso_cnt++);

	reg1.bi.b15 = 0;   // borro bit 15
    reg1.bi.b4 = 1;    // enciendo bit 1
	reg1.bi.b3 = 0;    // borro bit 3
    print_reg(reg1, caso_cnt++);

    return 0;
}


void print_reg(MY_REG reg, char caso)
{
	printf("case%c word-> %X \n", caso, reg.w.word); //ABCD
	printf("case%c lo -> %X \n", caso, reg.by.lo);  //CD
	printf("case%c hi -> %X \n", caso, reg.by.hi);  //AB
	printf("case%c b15 -> %X \n", caso, reg.bi.b15);  //0
	printf("\n");
}
