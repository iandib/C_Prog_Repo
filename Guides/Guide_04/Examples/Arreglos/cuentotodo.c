#include <stdio.h>

enum {IN, OUT};

void cuentotodo(const char arr[]);

/* count lines, words, and characters in input */
int main(void)
{
    char texto[] = "Aca estamos en clase, sin saber que hacer.\nY ahora? Ya se! Programamos..\nMejor no.";

    printf("Texto original:\n%s\n\n", texto);

    cuentotodo(texto);

    return 0;
}

void cuentotodo(const char arr[])
{
    int c, nl, nw, nc, state;

    state = OUT;
    nl = nw = nc = 0;

    while (arr[nc] != '\0')
    {
        c = arr[nc++];

        if (c == '\n')
            ++nl;
        if (c == ' ' || c == '\n' || c == '\t')
        {
            state = OUT;
        }
        else if (state == OUT)
        {
            state = IN;
            ++nw;
        }
    }

    if(nc > 0)
    {
        ++nl;
    }

    printf("Lineas: %d, Palabras: %d, Caracteres: %d\n", nl, nw, nc);
}


