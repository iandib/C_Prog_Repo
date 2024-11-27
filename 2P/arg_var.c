#include <stdio.h>
#include <stdarg.h>

void showVar(char* szTypes, ...);

int main(void)
{
    showVar("fcsi", 32.4f, 'a', "Test String", 4);
    return 0;
}

void showVar(char *szTypes, ...)
{
    va_list v1;
    int i;

    // szTypes is the last argument specified; you must access all others using the variable-argument macros
    va_start(v1, szTypes);

    // Step through the list
    for (i = 0; szTypes[i] != '\0'; ++i)
    {
        union Printable_t
        {
            int i;
            float f;
            char c;
            char *s;
        } Printable;

        // Type to expect
        switch (szTypes[i])
        { 

            // int is not promoted
            case 'i':
                Printable.i = va_arg(v1, int);
                printf("%i\n", Printable.i);
                break;
            
            // float is promoted to double in variadic arguments
            case 'f':
                Printable.f = va_arg(v1, double); 
                printf("%f\n", Printable.f);
                break;
            
            // char is promoted to int in variadic arguments
            case 'c':
                Printable.c = va_arg(v1, int);
                printf("%c\n", Printable.c);
                break;

            // Correctly specify char * for strings
            case 's':
                Printable.s = va_arg(v1, char *); 
                printf("%s\n", Printable.s);
                break;
        }
    }

    va_end(v1);
}
