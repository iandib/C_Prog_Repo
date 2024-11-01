#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "port_read.h"

extern port portA;

int main (void)
{
    initPins();

    portA.b0 = 0;
    portA.b1 = 0;
    portA.b2 = 0;
    portA.b3 = 0;
    portA.b4 = 0;
    portA.b5 = 0;
    portA.b6 = 0;
    portA.b7 = 0;

    char c;

    while((c = getchar()) != 'q' && c != 'Q')
    {
        printf("%c\n", c);
        if(c >= '0' && c <= '7')
        {
            switch(c - '0')
            {
                case 0:
                    portA.b0 = 1;
                    break;
                case 1:
                    portA.b1 = 1;
                    break;
                case 2:
                    portA.b2 = 1;
                    break;
                case 3:
                    portA.b3 = 1;
                    break;
                case 4:
                    portA.b4 = 1;
                    break;
                case 5:
                    portA.b5 = 1;
                    break;
                case 6:
                    portA.b6 = 1;
                    break;
                case 7:
                    portA.b7 = 1;
                    break;
                default: break;

            }
        }
        else if(c == 't' || c == 'T')
        {
            portA.b0 = portA.b0? 0: 1;
            portA.b1 = portA.b1? 0: 1;
            portA.b2 = portA.b2? 0: 1;
            portA.b3 = portA.b3? 0: 1;
            portA.b4 = portA.b4? 0: 1;
            portA.b5 = portA.b5? 0: 1;
            portA.b6 = portA.b6? 0: 1;
            portA.b7 = portA.b7? 0: 1;
        }
        else if(c == 's' || c == 'S')
        {
            portA.b0 = 1;
            portA.b1 = 1;
            portA.b2 = 1;
            portA.b3 = 1;
            portA.b4 = 1;
            portA.b5 = 1;
            portA.b6 = 1;
            portA.b7 = 1;
        }
        else if(c == 'c' c == 'C')
        {
            portA.b0 = 0;
            portA.b1 = 0;
            portA.b2 = 0;
            portA.b3 = 0;
            portA.b4 = 0;
            portA.b5 = 0;
            portA.b6 = 0;
            portA.b7 = 0;
        }
        port_read();
        while((c = getchar()) != '\n');
    }  

    endPins();
    
    return 0;
}