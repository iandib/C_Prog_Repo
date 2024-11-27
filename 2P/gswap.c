#include <stdio.h>

void gswap(void* p1, void* p2, int size)
{
    // Variable auxiliar para intercambiar bytes
    char aux;

    // Convertimos los punteros void* a char* para hacer aritmética de punteros byte a byte
    char* ptr1 = (char*) p1;
    char* ptr2 = (char*) p2;

    // Iteramos sobre cada byte del bloque de memoria de tamaño 'size'
    for (int i = 0; i < size; i++)
    {
        // Guardamos el byte actual de p1 en aux
        aux = ptr1[i];

        // Copiamos el byte actual de p2 en p1
        ptr1[i] = ptr2[i];

        // Copiamos el byte de aux en p2
        ptr2[i] = aux;
    }

/* ALTERNATIVA

    for (int i = 0; i < size; i++)
    {
        aux = *((char*) p1 + i);
        *((char*) p1 + i) = *((char*) p2 + i);
        *((char*) p2 + i) = aux;
    }

    obs: es necesario castear el puntero ANTES de sumar el desplazamiento, no se puede hacer 
    aritmética de punteros a void!
*/
}


int main()
{
    int a = 42, b = 99;
    printf("Before swap: a = %d, b = %d \n", a, b);

    // Intercambia valores de tipo int
    gswap(&a, &b, sizeof(int));

    printf("After swap: a = %d, b = %d\n", a, b);
    return 0;
}
