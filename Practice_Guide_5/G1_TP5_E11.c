/* ************************************************************
    * NOTAS INICIALES *
   ************************************************************ */

/*
Escribimos los mensajes en inglés para no tener conflictos con los caracteres que no vienen incluidos en la tabla ASCII.

Cambiamos los nombres de los parámetros que recibe la función swap, para que sean más ilustrativos. El funcionamiento es igual.

Los arrays en C van desde 0 hasta N-1, pero nuestra variable `nums_in_array` cuenta los elementos desde 1 hasta N. Por eso, para 
recorrer el array correctamente, usamos la condición `array_index < nums_in_array` (con menor estricto).

--------------- OPTIMIZACIÓN DE LA FUNCIÓN 'bubble_sort' ---------------

https://es.wikipedia.org/wiki/Ordenamiento_de_burbuja

La optimización de la función bubble_sort se basa en que, tras cada pasada sobre la lista, el número más grande siempre queda en 
su posición final. Esto significa que, en las siguientes pasadas, no es necesario volver a comparar ese número, ya que está en 
el lugar correcto.

En lugar de recorrer el array completo en cada pasada, se puede reducir el rango de comparación, omitiendo los números que ya están 
ordenados. Así, en la segunda pasada se recorre hasta el penúltimo elemento, en la tercera hasta el antepenúltimo, etc., lo que 
disminuye el número de comparaciones necesarias y optimiza el proceso de ordenamiento.
*/


/* ************************************************************
    * CONFIGURACIÓN GENERAL *
   ************************************************************ */

/* --------------- LIBRERÍAS UTILIZADAS --------------- */

// Librería estándar de entrada y salida en C
#include <stdio.h>

/* --------------- PARÁMETROS Y VARIABLES --------------- */

// Definimos una constante para fijar un máximo arbitrario de números que puede insertar el usuario
#define MAX_NUMS 50

// Definimos una macro para validar el caracter (c) insertado por el usuario
#define IS_VALID_DIGIT(c) ((c) >= '0' && (c) <= '9')

// Defino una macro para garantizar que el número insertado no genere overflow
#define PREVENT_OVERFLOW(n) (((n) < -999999999) || ((n) > 999999999))

// Creamos el array que contendrá los números a ordenar, lo inicializamos vacío
int array[MAX_NUMS] = {};

// Definimos una variable para contar la cantidad de números que inserta el usuario en el array
int nums_in_array = 0;

// Definimos una variable para contar la cantidad de cambios que se van realizando al ordenar el array
int swap_count = 0;

/* --------------- PROTOTIPOS DE LAS FUNCIONES --------------- */

/* La función lee los caracteres insertados por el usuario y guarda el número correspondiente en cada posición del array, hasta que 
presione Enter para confirmar */ 
int read_user_input(int array[]);

// La función calcula el número que quiere insertar el usuario, actualizando la potencia de 10 por la que tiene que multiplicar cada dígito
int compose_num(int current_num, int digit);

// La función añade el último número al array (revisando si es negativo) y actualiza las variables correspondientes
int update_array(int array[], int *num, unsigned char user_digit, int *index, int is_negative, int is_num_true);

// La función imprime la lista en el orden correspondiente a la instancia en la que se invoca
void print_list(int nums_in_array, int array[]);

/* Esta función compara cada elemento de un array con el de la posición siguiente, ubicando el menor en la posición más baja de las dos.
Esto se repite N-1 veces, hasta terminar de ordenar todos los elementos del array. */
void bubble_sort(int nums_in_array, int array[]);

// La función intercambia de posición los dos enteros que recibe
void swap(int* first_num, int* next_num);


/* ************************************************************
    * FUNCIÓN PRINCIPAL *
   ************************************************************ */

int main(void)
{
    /* --------------- VERIFICACIÓN DE ERRORES --------------- */
     
    /* Llamamos a la función que recibe los números del array, si devuelve -1 significa que hubo un error y terminamos la ejecución
    retornando 1 */
    if (read_user_input(array) == -1)
    {
        return 1;
    }   

    // Si no hubo errores al llamar a la función anterior, seguimos con la ejecución del programa
    else
    {
        /* --------------- MANEJO DE LAS LISTAS --------------- */

        // Imprimimos la lista original
        printf("List to sort: ");
        print_list(nums_in_array, array);

        // Llamamos a la función bubble_sort para ordenar la lista
        bubble_sort(nums_in_array, array);

        // Imprimimos la lista ordenada
        printf("Sorted list: ");
        print_list(nums_in_array, array);

        // Imprimimos la cantidad de intercambios que fueron necesarios para ordenar la lista
        printf("Swaps needed to sort the list: %d \n", swap_count);

        // Retornamos 0 como de costumbre
        return 0;       
    }   
}


/* ************************************************************
    * FUNCIÓN PARA RECIBIR EL INPUT DEL USUARIO *
   ************************************************************ */

/* La función lee los caracteres insertados por el usuario y guarda el número correspondiente en cada posición del array, 
hasta que presione Enter para confirmar */
int read_user_input(int array[])
{
    /* --------------- INICIALIZACIÓN DE VARIABLES --------------- */

    // Definimos una variable que almacenará el último caracter ingresado por el usuario
    unsigned char user_digit;

    // Definimos una variable que representará el número a guardar en cada posición del array y lo inicializamos en 0
    int new_num = 0;

    // Definimos una variable para determinar si el número que inserta el usuario es negativo
    int is_negative = 0;

    // Definimos una variable para determinar si el usuario ha ingresado un número
    int is_num_true = 0;

    // Definimos una variable que representará la posición en la que nos encontramos dentro del array
    int array_index = 0;

    // Solicitamos los números que se quieren agregar a la lista
    printf("Type the numbers you want to include on the list (separated by space or comma): ");

    /* --------------- MANEJO DEL INPUT --------------- */

    // Leemos los caracteres de entrada hasta que se presione Enter
    while ((user_digit = getchar()) != '\n')
    {
        /* Si el usuario inserta el símbolo '-' al inicio de un nuevo número (new_num = 0 por default), marcamos que el
        número es negativo */
        if ((user_digit == '-') && (new_num == 0))
        {
            is_negative = 1;
        }

        // Si el caracter insertado por el usuario es válido (dígito del '0' al '9')
        else if (IS_VALID_DIGIT(user_digit))
        {
            // Convertimos el dígito a entero y lo acumulamos en el número actual
            new_num = (new_num * 10) + (user_digit - '0');

            // Marcamos que el usuario ha ingresado un número
            is_num_true = 1;

            // Si el número insertado está fuera del rango permitido, retornamos -1 e imprimimos un mensaje de error
            if (PREVENT_OVERFLOW(new_num))
            {
                printf("Invalid input. Please enter a number between -999999999 and 999999999. \n");
                return -1;
            }
        }

        /* --------------- ACTUALIZACIÓN DEL ARRAY --------------- */

        // Si el usuario inserta una coma o espacio para separar los números
        else if ((user_digit == ',') || (user_digit == ' '))
        {
            /* Llamamos a la función para añadir el número al array, si devuelve -1 significa que hubo un error y 
            terminamos la ejecución retornando -1 nuevamente */
            if (update_array(array, &new_num, user_digit, &array_index, is_negative, is_num_true) == -1)
            {
                return -1;
            }

            // Reiniciamos el número actual, la marca de negativo y la marca de ingreso de número
            new_num = 0;
            is_negative = 0;
            is_num_true = 0;
        }

        // Si el usuario inserta un caracter inválido, retornamos -1 e imprimimos un mensaje de error
        else
        {
            printf("Invalid input. Please type only numbers. \n");
            return -1;
        }
    }

    /* --------------- ÚLTIMO ELEMENTO DEL ARRAY --------------- */

    /* Si el usuario no escribe una coma o un espacio antes de presionar Enter, el último número insertado no se guarda en 
    el ciclo While, por lo que hay que hacerlo manualmente. */
    if (update_array(array, &new_num, user_digit, &array_index, is_negative, is_num_true) == -1)
    {
        return -1;
    }

    // Si no hubo errores, retornamos 0
    return 0;
}


/* ************************************************************
    * FUNCIÓN PARA COMPONER UN NÚMERO A PARTIR DE DÍGITOS *
   ************************************************************ */

// La función calcula el número que quiere insertar el usuario, actualizando la potencia de 10 por la que tiene que multiplicar cada dígito
int compose_num(int current_num, int digit)
{
    // Multiplicamos el número actual por 10 y sumamos el nuevo dígito
    return (current_num * 10) + digit;
}


/* ************************************************************
    * FUNCIÓN PARA AÑADIR UN NÚMERO AL ARRAY *
   ************************************************************ */

// La función añade el último número al array (revisando si es negativo) y actualiza las variables correspondientes
int update_array(int array[], int *num, unsigned char user_digit, int *index, int is_negative, int is_num_true)
{
    /* Si el número es negativo (is_negative = 1) pero su formato es inválido, es decir, si no se inserta un número luego de presionar '-' 
    o si se inserta 0 (new_num = 0), retornamos -1 e imprimimos un mensaje de error */
    if ((is_negative) && (*num == 0))
    {
        printf("Invalid input. '-' must be followed by a non-zero number. \n");
        return -1;
    }

    /* --------------- ACTUALIZACIÓN DEL ARRAY --------------- */

    // Si realmente se insertó un número (no se dejó el espacio vacío), se guarda en la última posición del array
    if (is_num_true)
    {
        // Si el número es negativo y su formato es válido, lo convertimos antes de guardarlo
        if (is_negative)
        {
            *num = - *num;
        }

        // Guardamos el número en la posición actual del array
        array[*index] = *num;

        // Avanzamos a la siguiente posición del array
        (*index)++;

        // Incrementamos el contador de números en el array
        nums_in_array++;
    }

    // Si alcanzamos el límite máximo del array, retornamos -1 e imprimimos un mensaje de error
    if (*index >= MAX_NUMS)
    {
        printf("Invalid input. Maximum number of elements reached. \n");
        return -1;
    }

    // Si no hubo errores, retornamos 0
    return 0;
}


/* ************************************************************
    * FUNCIÓN PARA IMPRIMIR LA LISTA *
   ************************************************************ */

// La función imprime la lista en el orden correspondiente a la instancia en la que se invoca
void print_list(int nums_in_array, int array[])
{   
    // Definimos una variable que representará la posición en la que nos encontramos dentro del array
    int array_index;

    // Recorremos todas las posiciones del array, desde el 0 hasta N-1
    for (array_index = 0; array_index < (nums_in_array); array_index++)
    {
        // Imprimimos el número que se encuentra en esa posición del array 
        printf("%d", array[array_index]);

        // Si no estamos en el último número (posición N-1), imprimimos una coma y espacio
        if (array_index < (nums_in_array - 1))
        {
            printf(", ");
        }
    }

    printf("\n");

    // La función no retorna nada
    return;
}


/* ************************************************************
    * FUNCIÓN BURBUJA *
   ************************************************************ */

/* Esta función compara cada elemento de un array con el de la posición siguiente, ubicando el menor en la posición más baja de las dos.
Esto se repite N-1 veces, hasta terminar de ordenar todos los elementos del array. */
void bubble_sort(int nums_in_array, int array[])
{
    // Definimos una variable para contar la cantidad de pasadas que se van haciendo sobre el array
    int bubble_runs;

    // Definimos una variable que representará la posición en la que nos encontramos dentro del array
    int array_index;
    
    // Pasamos sobre el array N-1 veces (como son pasadas, iniciamos desde la número 1)
    for (bubble_runs = 1; bubble_runs < (nums_in_array); bubble_runs++)
    {
        /* En cada pasada, recorremos todas las del array, desde 0 hasta N-1-b (donde b es el número de pasada). Esto permite optimizar la 
        función, como se explica en las notas iniciales. */
        for (array_index = 0; array_index < (nums_in_array - bubble_runs); array_index++)
        {
            // Revisamos si el elemento en la posición actual es mayor que el de la posición siguiente
            if (array[array_index] > array[array_index + 1])
            {
                // Si es el caso, intercambiamos los elementos de ambas posiciones e incrementamos el contador de cambios en 1
                swap(&array[array_index], &array[array_index + 1]);
                swap_count += 1;
            }
        }
    }
    
    // La función no retorna nada
    return;
}


/* ************************************************************
    * FUNCIÓN PARA CAMBIAR LOS NÚMEROS DE POSICIÓN *
   ************************************************************ */

// La función intercambia de posición los dos enteros que recibe
void swap(int *p_numA, int *p_numB)
{
    // Guardamos el valor del número A en una variable temporal
    int temp = *p_numA;

    // Guardamos el valor del número B en el número A
    *p_numA = *p_numB;

    // Guardamos el valor del número A, que quedó en la variable temporal, en el número B
    *p_numB = temp;

    // La función no retorna nada, porque con los punteros modificamos los valores de las variables originales
    return;
}


