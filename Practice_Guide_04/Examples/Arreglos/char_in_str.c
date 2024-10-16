#include <stdio.h>

int char_in_str(char arr[], char c);

/* count lines, words, and characters in input */
int main(void)
{
    char texto[] = "Aca estamos en clase, sin saber que hacer.\nY ahora? Ya se! Programamos..\nMejor no.";
	char letra = 'c';

    printf("Texto original: INICIO\n%s\n", texto);
	printf("Texto original: FIN\n\n");

	printf("Caracter a buscar: %c\n", letra);
	printf("Veces encontradas: %d\n", char_in_str(texto, letra));

    return 0;
}

int char_in_str(char arr[], char c)
{
    int c_count = 0, i = 0;

	while (arr[i] != '\0')
    {
        if (arr[i] == c)
		{
			++c_count;
		}
		++i;
	}

	return c_count;
}



