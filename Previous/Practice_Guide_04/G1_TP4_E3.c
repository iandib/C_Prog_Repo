#include <stdio.h>

// Creamos una macro para validar el caracter insertado por el usuario
#define IS_VALID_DIGIT(c) ((c) >= '0' && (c) <= '9')
// Creamos una constante con la cantidad de números que puede recibir el array
#define MAX_INPUT 1000

/* --------------- PROTOTIPOS DE LAS FUNCIONES --------------- */
// Función para calcular el promedio
double prom_calculator(double array[], unsigned int array_size);
// Función para leer los caracteres del usuario
unsigned int read_user_input(double array[]);
// Función para convertir dígitos consecutivos en un número
int compose_number(int current_number, int digit);


// ************************************************************
//      * FUNCIÓN PRINCIPAL *
// ************************************************************

int main(void)
{
    // Defino el array que guardará los valores del usuario
    double array[MAX_INPUT] = {};
    
    // Tamaño actual del arreglo
    unsigned int array_size;

    // Leemos la entrada del usuario y obtenemos el tamaño del array
    array_size = read_user_input(array);

    // Si la entrada es válida (tamaño mayor a 0), calculamos e imprimimos el promedio
    if (array_size > 0)
    {
        // Promedio de los números en el arreglo
        double array_prom = prom_calculator(array, array_size);

        printf("The promedy of the typed numbers is %f\n", array_prom);
    }
    
    return 0;
}

// ************************************************************
//      * FUNCIÓN PARA RECIBIR LOS NÚMEROS DEL USUARIO *
// ************************************************************

unsigned int read_user_input(double array[])
{
    // Variable para almacenar el dígito del usuario
    unsigned char user_digit;

    // Número que se está construyendo
    int current_number = 0;

    // Posición actual del arreglo
    int array_position = 0;

    printf("Type the numbers separated by commas (you can use spaces before commas): ");

    /* --------------- ACTUALIZACIÓN DEL ARREGLO --------------- */
    
    while ((user_digit = getchar()) != '\n')
    {
        if (IS_VALID_DIGIT(user_digit))
        {
            // Convertimos el dígito a entero y lo añadimos al número actual
            current_number = compose_number(current_number, user_digit - '0');
        }
        else if (user_digit == ' ')
        {
            // Si es un espacio, simplemente lo ignoramos
            continue;
        }
        else if (user_digit == ',')
        {
            // Si encontramos una coma, guardamos el número completo en el array
            array[array_position] = current_number;
            array_position++;

            // Reiniciamos current_number para el próximo número
            current_number = 0;
        }
        else
        {
            // Si el usuario inserta un caracter no válido, mostramos el error
            printf("Error: Invalid input, please insert digits (0-9), commas, and spaces only.\n");
            return 0;  // Regresamos 0 para indicar que la entrada no es válida
        }
    }

    // Guardamos el último número en el array si no termina con una coma
    array[array_position] = current_number;
    array_position++;

    // Retornamos el tamaño del array (cantidad de números ingresados)
    return array_position;
}

// ************************************************************
//      * FUNCIÓN PARA COMPONER UN NÚMERO A PARTIR DE DÍGITOS *
// ************************************************************

int compose_number(int current_number, int digit)
{
    /* --- MULTIPLICAMOS EL NÚMERO ACTUAL POR 10 Y AÑADIMOS EL NUEVO DÍGITO --- */
    return (current_number * 10) + digit;
}

// ************************************************************
//      * FUNCIÓN PARA CALCULAR EL PROMEDIO *
// ************************************************************

double prom_calculator(double array[], unsigned int array_size)
{
    unsigned int i;
    double sum = 0;

    /* --- SUMA DE LOS ELEMENTOS DEL ARREGLO --- */
    for(i = 0; i < array_size; i++)
    {
        sum += array[i];
    }

    /* --- CÁLCULO DEL PROMEDIO --- */
    return (sum / array_size);
}
