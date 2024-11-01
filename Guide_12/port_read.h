#ifndef PORT_READ
#define PORT_READ

void port_read (void);

typedef struct 
{
    int b0;
    int b1;
    int b2;
    int b3;
    int b4;
    int b5;
    int b6;
    int b7;
} port;

port portA;

#endif