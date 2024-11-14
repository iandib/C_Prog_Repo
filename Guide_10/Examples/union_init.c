#include <stdio.h>

#define PI 3.14159265359L

#define VOL_PRISMA(x, y, z)     ((double)((x)*(y)*(z)))
#define VOL_ESFERA(r)           ((double)(4.0*PI*(r)*(r)*(r)/3.0))


typedef union
{
    struct {int x; int y; int z; } pris;
    double rad;
} pieza_t;


//======================================================================================
int main(void)
{
    pieza_t cubo = {.pris = {3, 3, 3}};
    pieza_t esfera = {.rad = 1.0};

    printf("Volumen prisma: %.2f\n", VOL_PRISMA(cubo.pris.x, cubo.pris.y, cubo.pris.z));
    printf("Volumen esfera: %.2f\n", VOL_ESFERA(esfera.rad));

    return 0;
}

