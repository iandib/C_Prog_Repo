/*
 * Different types
 *
 * Minimal program depicting variadic functions.
 *
 * Depicts usage different data types in the list of
 * variadic arguments, and highlights argument promotion.
 *
 * 22.07 Programación I @ Instituto Tecnológico de Buenos Aires, 2017
 */

#include <stdio.h>
#include <stdarg.h>


/*
 * Show Variables
 * Takes a format string of the form
 * "ifcs", where each character specifies the
 * type of the argument in that position.
 *
 * i = int
 * f = float
 * c = char
 * s = string (char *)
 *
 * Following the format specification is a variable
 * list of arguments. Each argument corresponds to
 * a format character in the format string to which
 * the szTypes parameter points
 *
 */
void showVar(char *szTypes, ...);



int main() {
   showVar("fcsi", 32.4f, 'a', "Test string", 4);
}

void showVar(char *szTypes, ...) {
   va_list vl;
   int i;

   //  szTypes is the last argument specified; you must access
   //  all others using the variable-argument macros.
   va_start(vl, szTypes);

   // Step through the list.
   for(i = 0; szTypes[i] != '\0'; ++i) {

      union Printable_t {
         int    i;
         float  f;
         char   c;
         char  *s;
      } Printable;

      switch(szTypes[i]) {   // Type to expect.
         case 'i':
            Printable.i = va_arg(vl, int);
            printf("%i\n", Printable.i);
         break;

         case 'f':
             Printable.f = va_arg(vl, double);
             printf("%f\n", Printable.f);
         break;

         case 'c':
             // Printable.c = va_arg( vl, char );   // uncomment this line, then comment next one and see whats comes out
                                                    // Then read this: http://stackoverflow.com/questions/28054194/char-type-in-va-arg
             Printable.c = va_arg(vl, int);         // implicit conversion from char to int
             printf("%c\n", Printable.c);
         break;

         case 's':
             Printable.s = va_arg(vl, char *);
             printf("%s\n", Printable.s);
         break;

         default:
         break;
      }
   }
   va_end(vl);
}

