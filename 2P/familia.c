#include <stdio.h>

// Define tamaño máximo para strings y arreglos de punteros
#define CHAR 50
#define NMAX 10

// Estructura que representa a una persona con información personal, familiares y relaciones
typedef struct persona
{
    // Nombre de la persona
    char nombre[CHAR];

    // Apellido de la persona
    char apellido[CHAR];

    // Fecha de nacimiento (día, mes, año)
    int nacimiento[3];

    // Punteros a los padres (máximo NMAX)
    struct persona* padres[NMAX];

    // Punteros a los hermanos (máximo NMAX)
    struct persona* hermanos[NMAX]; 

    // Punteros a los hijos (máximo NMAX)
    struct persona* hijos[NMAX];
} persona_t;


// Calcula la cantidad de sobrinos de un miembro de la familia
int cantSobrinos(persona_t* familiar)
{
    // Inicializa el contador de sobrinos
    int sobrinos = 0;

    // Recorre el arreglo de hermanos del miembro de la familia
    for (int i = 0; i < NMAX && familiar->hermanos[i] != NULL; i++)
    {
        // Obtiene el hermano actual
        persona_t* hermano = familiar->hermanos[i];

        // Recorre los hijos del hermano para contar los sobrinos
        for (int j = 0; j < NMAX && hermano->hijos[j] != NULL; j++)
        {
            sobrinos++;
        }
    }

    // Retorna la cantidad total de sobrinos
    return sobrinos;
}

