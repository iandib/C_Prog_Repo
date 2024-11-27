#include <stdlib.h>

#define ERROR -1
#define SUCCESS 1

// Nodo de la lista
typedef struct nodo
{
    int data;
    struct nodo* pNext;
} nodo_t;

// Función para agregar un nodo al final de la lista
int listAdd(nodo_t* first, int newData)
{
    // Reservar memoria dinámica para el nuevo nodo
    nodo_t* last = (nodo_t*) malloc(sizeof(nodo_t));

    // Verificar si malloc falló
    if (last == NULL)
    {
        return ERROR;
    }

    // Asignar el nuevo dato
    last->data = newData;

    // El nuevo nodo apunta a NULL (es el último)
    last->pNext = NULL;

    // Si la lista está vacía
    if (first == NULL)
    {
        first = last;
        return SUCCESS;
    }

    // Recorrer la lista hasta el último nodo
    nodo_t* current = first;
    while (current->pNext != NULL)
    {
        current = current->pNext;
    }

    // Conectar el nuevo nodo al final de la lista
    current->pNext = last; 

    return SUCCESS;
}
