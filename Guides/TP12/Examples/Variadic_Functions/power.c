/*
 * Power Summation
 *
 * Minimal program depicting variadic functions.
 *
 * Depicts usage of the four main stdargs macros
 * (va_list, va_start, va_arg, va_end)
 * through a power summation.
 *
 *
 * To compile don't forget to link the math library:
 * gcc power.c -o power -lm
 *
 *
 * 22.07 Programación I @ Instituto Tecnológico de Buenos Aires, 2017
 */

#include <stdio.h>
#include <stdarg.h>
#include <math.h>

/*
 * Power Summation
 * Input:
 *   noParams: Number of variadic arguments
 *   raiseTo:  power to be used for every number
 *   ...:      List of double numbers to be averaged
 * Output:
 *   Sum of powers of every variadic argument
 *
 * Usage:
 *   double psum = powerSummation(3, 2, 1, 2, 3)
 *   psum == 14
 */
double powerSummation(long noParams, int raiseTo, ...);

int main(void) {
    double total;
    total = powerSummation(3, 2, 1.0f, 2.0f, 3.0f);
    printf("Result 1: %f\r\n", total);

    total = powerSummation(4, 3, 2.0f, 1.0f, 2.0f, 3.0f);
    printf("Result 2: %f\r\n", total);

    return 0;
}

double powerSummation(long noParams, int raiseTo, ...) {

  va_list paramList;
  va_start(paramList, raiseTo);

  double sum = 0;
  long i;

  for (i=0; i<noParams; i++) {
      double base = va_arg(paramList, double);
      sum = sum + pow(base, raiseTo);
  }

  va_end(paramList);

  return sum;
}


