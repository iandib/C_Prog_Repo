/* ************************************************************
    * CONFIGURACIÓN GENERAL *
   ************************************************************ */

/* --------------- LIBRERÍAS UTILIZADAS --------------- */

// Librería estándar de entrada y salida en C
#include <stdio.h>

/* --------------- CONSTANTES --------------- */

// Definimos una constante para fijar un máximo arbitrario de números que puede insertar el usuario
#define total_nums 2

/* --------------- PROTOTIPOS DE LAS FUNCIONES --------------- */

// La función imprime la lista en el orden correspondiente a la instancia en la que se invoca
void print_list(int array[]);

// La función intercambia de posición los dos enteros que recibe
void swap(int* first_num, int* next_num);


/* ************************************************************
    * FUNCIÓN PRINCIPAL *
   ************************************************************ */

// La función principal imprime los mensajes en pantalla y llama a las otras funciones
int main(void)
{
    // Definimos una variable para guardar los números de la lista
    int num1 = 9;
    int num2 = 7;

    // Creamos un array con los números de la lista
    int array[total_nums] = {num1, num2};

    /* --------------- IMPRESIÓN DE LA LISTA ORIGINAL --------------- */

    printf("List to swap: ");
    print_list(array);

    /* --------------- SWAP DE LA LISTA --------------- */
    
    // Llamamos a la función swap pasándole la dirección de cada posición del array
    swap(&array[0], &array[1]);

    /* --------------- IMPRESIÓN DE LA LISTA MODIFICADA --------------- */

    printf("Lista modificada: ");
    print_list(array);

    return 0;
}


/* ************************************************************
    * FUNCIÓN QUE IMPRIME LA LISTA *
   ************************************************************ */

// La función imprime la lista en el orden correspondiente a la instancia en la que se invoca
void print_list(int array[])
{   
    // Recorremos todas las posiciones del array, desde el 0 hasta N-1
    for (int array_index = 0; array_index < total_nums; array_index++)
    {
        // Imprimimos el número que se encuentra en esa posición del array 
        printf("%d", array[array_index]);

        // Si no estamos en el último número, imprimimos una coma y espacio
        if (array_index < (total_nums - 1))
        {
            printf(", ");
        }
    }

    printf("\n");

    // No es necesario que la función retorne nada
    return;
}


/* ************************************************************
    * FUNCIÓN SWAP *
   ************************************************************ */

// La función intercambia de posición los dos enteros que recibe

void swap(int *p1, int *p2)
{
    int temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;

    return;
}
