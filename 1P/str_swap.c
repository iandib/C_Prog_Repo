#include <stdio.h>

// Función que intercambia dos elementos de un arreglo de punteros a char
void swap(char **a, char **b) 
{
    // Intercambia los punteros
    char *temp = *a;
    *a = *b;
    *b = temp;
}

// Función que imprime el contenido de un arreglo de strings
void print_array(char *nombres[], int size) 
{
    for (int i = 0; i < size; i++) 
    {
        printf("%s ", nombres[i]);
    }
    printf("\n");
}

int main() 
{
    // Declaración del arreglo de nombres
    char *nombres[] = {"Alan", "Frank", "Mary"};
    
    // Tamaño del arreglo
    int size = sizeof(nombres) / sizeof(nombres[0]);
    
    // Imprime el arreglo antes del swap
    printf("Antes del swap:\n");
    print_array(nombres, size);
    
    // Intercambia el primer y tercer elemento
    swap(&nombres[0], &nombres[2]);
    
    // Imprime el arreglo después del swap
    printf("Después del swap:\n");
    print_array(nombres, size);
    
    return 0;
}
