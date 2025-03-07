#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float gen_ran(float min, float max)
{
    return min + ((float)rand() / RAND_MAX) * (max - min);
}

int main(void)
{
    float n = 5.5f;
    float m = 7.8f;
    
    // Inicializar el generador de números aleatorios
    srand((unsigned int)time(NULL));

    float r1 = gen_ran(0.0f, 1.0f);
    float r2 = gen_ran(0.0f, n);
    float r3 = gen_ran(n, m);

    // Generar números pseudoaleatorios en diferentes rangos
    printf("Random number in range [0.0, 1.0]: %f \n", r1);
    printf("Random number in range [0.0, %f]: %f \n", n, r2);
    printf("Random number in range [%f, %f]: %f \n", n, m, r3);

    return 0;
}
