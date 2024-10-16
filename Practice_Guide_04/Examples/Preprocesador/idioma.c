#include <stdio.h>

#define CASTELLANO 1
#define INGLES 2
#define ALEMAN 3

#define IDIOMA INGLES


#ifndef IDIOMA
#error No hay idioma definido
#elif IDIOMA == CASTELLANO
#define SALUDO_INICIAL	"Hola"
#define SALUDO_FINAL	"Chau"
#elif IDIOMA == INGLES
#define SALUDO_INICIAL	"Hello"
#define SALUDO_FINAL	"Good Bye"
#elif IDIOMA == ALEMAN
#define SALUDO_INICIAL	"Hallo"
#define SALUDO_FINAL	"Tschus"
#else
#error FALTA DEFINIR UN IDIOMA!
#endif // IDIOMA == xx


int main(void)
{
    printf(SALUDO_INICIAL "\n");
	printf(SALUDO_FINAL "\n");
    return 0;
}
