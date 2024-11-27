#include <string.h>

#define CHAR 50
#define NMAX 10

// Constantes de retorno
#define JUGARON 1
#define NO_JUGARON -1

// Estructura para almacenar la información de un futbolista
typedef struct 
{
    // Nombre y apellido (campos no utilizados)
    char nombre[CHAR];
    char apellido[CHAR];

    // Arreglo de punteros a cadenas (nombres de clubes)
    char* clubes[NMAX];

    // Año inicial en cada club
    int inicios[NMAX];

    // Año final en cada club
    int salidas[NMAX];
} futbolista_t;


// Función para verificar si dos jugadores jugaron juntos
int jugaron_juntos(futbolista_t* jugadorA, futbolista_t* jugadorB)
{
    // Iterar sobre los clubes de jugadorA
    for (int i = 0; jugadorA->clubes[i] != NULL; i++)
    {
        // Iterar sobre los clubes de jugadorB
        for (int j = 0; jugadorB->clubes[j] != NULL; j++)
        {
            // Verificar si ambos jugadores estuvieron en el mismo club y si sus periodos en el club se solapan
            if ((strcmp(jugadorA->clubes[i], jugadorB->clubes[j]) == 0) &&
                jugadorA->inicios[i] <= jugadorB->salidas[j] && 
                jugadorA->salidas[i] >= jugadorB->inicios[j])
                {
                    return JUGARON;
                }
        }
    }

    // No jugaron juntos
    return NO_JUGARON;
}


int main()
{
    // Crear futbolistas
    futbolista_t jugadorA =
    {
        "Lionel",
        "Messi",
        {"Barcelona", "PSG", NULL},
        {2000, 2021},
        {2021, 2023}
    };

    futbolista_t jugadorB =
    {
        "Neymar",
        "Junior",
        {"Santos", "Barcelona", "PSG", NULL},
        {2009, 2013, 2017},
        {2013, 2017, 2023}
    };

    // Verificar si jugaron juntos
    if (jugaron_juntos(&jugadorA, &jugadorB) == JUGARON)
    {
        printf("Jugaron juntos en algún club. \n");
    }

    else
    {
        printf("No jugaron juntos en ningún club. \n");
    }

    return 0;
}

