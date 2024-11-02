/*
 * Average
 *
 * Minimal program depicting variadic functions.
 *
 * Depicts usage of the four main stdargs macros
 * (va_list, va_start, va_arg, va_end)
 * through a simple average function that averages
 * a list of integer arguments.
 *
 * 22.07 Programación I @ Instituto Tecnológico de Buenos Aires, 2017
 */

#include <stdio.h>
#include <stdarg.h>

/*
 * Average
 * Input:
 *   num: Number of variadic arguments
 *   ...: List of integer numbers to be averaged
 * Output:
 *   Arithmetic mean of the num first variadic arguments
 *
 * Usage:
 *   double mean = average(3, 1, 2, 3)
 *   mean == 2
 */
double average(int num, ...);

void main(void)
{
   printf("Average of 2, 3, 4, 5 = %f\n", average(4, 2, 3, 4, 5));
   printf("Average of 5, 10, 15 = %f\n", average(3, 5, 10, 15));
}

double average(int num, ...)
{

    va_list valist;
    double sum = 0.0;
    int i;

    // Initialize valist for num number of arguments
    va_start(valist, num);

    // Access all the arguments assigned to valist
    for (i = 0; i < num; i++)
    {
       sum += va_arg(valist, int);
    }

    // Clean memory reserved for valist
    va_end(valist);

    return sum/num;
}
