#include <stdio.h>

double power (double base, int n);

int main (void)
{
    double num = 2;
    int pow = 8;
    printf("%f ^ %d = %f\n", num, pow, power(num, pow)); // pruebo funcion
    
    pow =-pow;
    printf("%f ^ %d = %f\n", num, pow, power(num, pow)); // pruebo funcion
    
    pow =-pow;
    num = 1.0/num;
    printf("%f ^ %d = %f\n", num, pow, power(num, pow)); // pruebo funcion

    return 0;
}


double power (double base, int n)
{
    double rta;

    if (n < 0)
    {
        n = -n;
        base = 1.0/base;
    }
    
    for (rta = 1.0; n > 0 ; --n)
    {
        rta *= base;
    }

    return rta;
}
