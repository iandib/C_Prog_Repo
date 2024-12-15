#include <stdio.h>

#define TEMP_MIN    -5.0
#define TEMP_MAX    40.0
#define TEMP_DELTA   0.1

int main (void)
{
    float temp_now;

    for (temp_now = TEMP_MIN ; temp_now <= TEMP_MAX ; temp_now += TEMP_DELTA)
    {
        printf("La temperartura actual es %.1f °C. ", temp_now);

        if (temp_now < 0.0)
            printf("Me congelo!\n");
        else if (temp_now < 10.0)
            printf("Muy frio!\n");
        else if (temp_now < 18.0)
            printf("Frio\n");
        else if (temp_now < 28.0)
            printf("Agradable\n");
        else if (temp_now < 35.0)
            printf("Caluroso!\n");
        else
            printf("Me derrito!!!\n");
    }

    return 0;
}
