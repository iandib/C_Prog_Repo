#include <stdio.h>

// Defino el orden máximo de la serie (cantidad de términos que se suman)
#define ORDER 10

// Función que calcula el factorial de un número
long long factorial(int num)
{
    long long result = 1;
    for (int i = 2; i <= num; i++)
    {
        result *= i;
    }
    return result;
}

// Función que calcula la potencia de un número de forma iterativa
double power(double base, int exponent)
{
    double result = 1.0;
    for (int i = 0; i < exponent; i++)
    {
        result *= base;
    }
    return result;
}

// Función que calcula la serie de Taylor para seno(x)
double sine_taylor_series(double x)
{
    double sum = 0.0;

    // Bucle para calcular cada término de la serie hasta el orden definido
    for (int n = 0; n < ORDER; n++)
    {
        // Calculamos el término de la serie (-1)^n * x^(2n+1) / (2n+1)!
        double term = power(x, 2*n + 1) / factorial(2*n + 1);

        // Alternamos entre sumar y restar términos de la serie
        if (n % 2 == 0)
        {
            sum += term;  // Si n es par, sumamos el término
        }
        else
        {
            sum -= term;  // Si n es impar, restamos el término
        }
    }

    return sum;
}

int main(void)
{
    // Definimos el valor de x para el cual queremos calcular el seno
    double x;

    // Solicitamos al usuario que introduzca el valor de x
    printf("Enter the value of x (in radians): ");
    scanf("%lf", &x);

    // Calculamos el seno de x usando la serie de Taylor
    double sine_value = sine_taylor_series(x);

    // Imprimimos el resultado
    printf("The approximation of sin(%.2f) using Taylor series is: %.10f\n", x, sine_value);

    return 0;
}
