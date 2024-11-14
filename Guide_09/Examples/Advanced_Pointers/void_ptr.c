#include <stdio.h>
#include <stdlib.h>

void myMemcpy(void * pD, const void *pO, unsigned int len);

const char str1[] = "Este es el string origen, solo lectura";
char str2[64];


int main(void)
{
    printf("String Origen:\n%s\n", str1);
    printf("String Destino:\n%s\n", str2);

    myMemcpy(str2, str1, sizeof(str1));

    printf("String Origen:\n%s\n", str1);
    printf("String Destino:\n%s\n", str2);

    return 0;
}


void myMemcpy(void * pD, const void *pO, unsigned int len)
{
    unsigned int nCiclos, i;
    int *p2intD;
    const int *p2intO;

    char *p2charD;
    const char *p2charO;

    // copio de a int
    nCiclos = len/sizeof(int);
    p2intO = pO;
    p2intD = pD;


    for (i=0 ; i<nCiclos ; i++)
    {
        *p2intD++ = *p2intO++; // copio elemento e incremento
    }

    // copio de a char
    nCiclos = len%sizeof(int);
    p2charO = (const char*) p2intO;
    p2charD = (char*) p2intD;

    for (i=0 ; i<nCiclos ; i++)
    {
        *p2charD++ = *p2charO++; // copio elemento e incremento
    }
}

