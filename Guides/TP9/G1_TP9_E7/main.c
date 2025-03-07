/* *****************************************************************
    *                       NOTAS INICIALES                       *
   ***************************************************************** */

// El primer número puede ser negativo, pero el segundo debe ser positivo.


/* *****************************************************************
    *                  CONFIGURACIÓN DEL ARCHIVO                  *
   ***************************************************************** */

/* --------------------- LIBRERÍAS UTILIZADAS --------------------- */

// Librería estándar de entrada y salida en C
#include <stdio.h>

// Librería para trabajar con booleanos (verdadero y falso)
#include <stdbool.h>

/* ---------------------- HEADERS UTILIZADOS ------------------------ */

// Header correspondiente al archivo que recibe y procesa el input del usuario
#include "Front_End/get_input.h"

// Header correspondiente al archivo que realiza las operaciones matemáticas
#include "Back_End/operate.h"

/* -------------------------- CONSTANTES -------------------------- */

// Definimos una constante de error al agregar operadores
#define UPDATE_ERROR -3

/* ----------------- VARIABLES GLOBALES PÚBLICAS ----------------- */

// Definimos un arreglo para almacenar los operadores permitidos
char operators[MAX_OPERATORS];

// Definimos un arreglo de punteros a las funciones que realizan las operaciones permitidas
double (*operations[MAX_OPERATORS])(double, double);

// Definimos una flag para verificar si ambos operandos están listos
bool operands_ready = false;

/* ----------------- VARIABLES GLOBALES PRIVADAS ----------------- */

// Definimos una variable para contar el número de operadores agregados
static int added_operators = 0;

/* --------------- PROTOTIPOS DE FUNCIONES PRIVADAS --------------- */

// La función agrega operadores al arreglo 'operators' y punteros a las operaciones al arreglo 'operations'
static int add_operators(char operator, double (*operation)(double, double));

// La función reinicia los operandos y el resultado para que no tengan  valor residual luego de cada operación
static void reset_values(double *first_operand, double *second_operand, double *result);


/* *****************************************************************
    *                      FUNCIÓN PRINCIPAL                      *
   ***************************************************************** */

int main(void)
{
    /* ------------------- VARIABLES LOCALES ------------------- */

    // Definimos un arreglo para almacenar los dos operandos
    double operands[MAX_OPERANDS] = {0.0, 0.0};

    // Definimos una variable que guarda el índice correspondiente al operador insertado
    int operator_index = 0;

    // Definimos una variable para almacenar el resultado de la operación
    double result = 0;

    /* -------------------- INICIALIZACIÓN -------------------- */

    // Informamos que se está iniciando la calculadora
    printf("Starting basic math calculator (press 'I' for info)... \n");

    // Agregamos las operaciones básicas a los arreglos correspondientes
    add_operators('+', add);
    add_operators('-', subtract);
    add_operators('*', multiply);
    add_operators('/', divide);
    add_operators('^', power);
    add_operators('r', root);

    /* --------------------- PROCESAMIENTO --------------------- */

    // Mientras el usuario no presione 'E', 'e' ni caracteres inválidos
    while (read_user_input(&operands[0], &operands[1], &operator_index, &result) != EXIT_REQUEST)
    {

        // Si el caracter ingresado no es válido (no hay un operador asociado)
        if (operator_index == OPERATOR_ERROR)
        {
            // Imprimimos un mensaje de error
            printf("Invalid input. Please type valid characters only. \n");

            // Reinicio los operandos y el resultado
            reset_values(&operands[0], &operands[1], &result);
        }

        // Si los caracteres ingresados completan una operación aritmética permitida
        else if (operands_ready)
        {
            // Si el operador es de potencia o raíz, y el segundo operando ingresado no es entero
            if ((operators[operator_index] == '^' || operators[operator_index] == 'r') && (!is_integer(operands[1])))
            {
                // Imprimimos un mensaje de advertencia
                printf("Warning: The second number is not an integer \n");

                // Reinicio los operandos y el resultado
                reset_values(&operands[0], &operands[1], &result);
            }

            // Si este no es el caso
            else
            {
                // Llamamos a la función correspondiente y almacenamos el resultado
                result = operations[operator_index](operands[0], operands[1]);

                // Mostramos el resultado de la operación
                printf("Result: %.2f \n", result);

                // Reinicio los operandos y el resultado
                reset_values(&operands[0], &operands[1], &result);
            }
        }
    }

    // Retornamos 0 si todo funciona correctamente
    return 0;
}


/* *****************************************************************
    *               FUNCIÓN PARA AGREGAR OPERADORES               *
   ***************************************************************** */

// La función agrega operadores al arreglo 'operators' y punteros a las operaciones al arreglo 'operations'
static int add_operators(char operator, double (*operation)(double, double))
{
    // Si no hay espacio para agregar más operadores
    if (added_operators >= MAX_OPERATORS) 
    {
        // Imprimimos un mensaje de error
        printf("Error. Max number of operators reached");
        
        // Retornamos 'UPDATE_ERROR' (-3)
        return UPDATE_ERROR;
    }

    // Agregamos el operador y su función correspondiente
    operators[added_operators] = operator;
    operations[added_operators] = operation;
    
    // Incrementamos el contador de operadores añadidos
    added_operators++;

    // Retornamos 0 si todo funciona correctamente
    return 0;
}


/* *****************************************************************
    *                FUNCIÓN PARA LIMPIAR MEMORIA                 *
   ***************************************************************** */

// La función reinicia los operandos y el resultado para que no tengan  valor residual luego de cada operación
static void reset_values(double *first_operand, double *second_operand, double *result)
{
    // Reinicio el resultado
    *result = 0;

    // Reinicio ambos operandos
    *first_operand = 0;
    *second_operand = 0;
}

