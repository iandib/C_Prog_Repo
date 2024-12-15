/* *****************************************************************
    *                  CONFIGURACIÓN DEL ARCHIVO                  *
   ***************************************************************** */

/* ---------------------- HEADERS UTILIZADOS ---------------------- */

// Header correspondiente a este archivo
#include "operate.h"

/* *****************************************************************
    *                    FUNCIONES MATEMÁTICAS                    *
   ***************************************************************** */

/* ---------------------- FUNCIÓN PARA SUMA ---------------------- */

// La función devuelve la suma de first_number y second_number
double add(double first_number, double second_number)
{
    return ((first_number) + (second_number));
}


/* ---------------------- FUNCIÓN PARA RESTA --------------------- */

// La función devuelve la diferencia entre first_number y second_number
double subtract(double first_number, double second_number)
{
    return ((first_number) - (second_number));
}


/* ------------------ FUNCIÓN PARA MULTIPLICACIÓN ---------------- */

// La función devuelve el producto de first_number y second_number
double multiply(double first_number, double second_number)
{
    return ((first_number) * (second_number));
}


/* --------------------- FUNCIÓN PARA DIVISIÓN ------------------- */

// La función devuelve el cociente entre first_number y second_number
double divide(double first_number, double second_number)
{
    // Si second_number es igual a 0
    if (second_number == 0)
    {
        // Imprimimos un mensaje de error
        printf("Error: Undefined Expression \n");

        // Retornamos 'OPERATION_ERROR' (-1)
        return OPERATION_ERROR;
    }

    // En caso contrario, retornamos el cociente entre first_number y second_number
    return ((first_number) / (second_number));
}


/* ------------------ FUNCIÓN PARA POTENCIACIÓN ------------------ */

// La función eleva first_number a la potencia entera que indica second_number
double power(double first_number, double second_number)
{
    // Casteo second_number a int y lo guardo en new_number
    int new_number = (int)(second_number);

    // Si tanto first_number como second_number son iguales a 0
    if ((first_number) == 0.0 && new_number == 0)
    {
        // Imprimimos un mensaje de error
        printf("Error: Undefined Expression \n");

        // Retornamos 'OPERATION_ERROR' (-1)
        return OPERATION_ERROR;
    }

    // En caso contrario, retornamos first_number elevado a la potencia new_number
    return (pow(first_number, new_number));
}


/* --------------------- FUNCIÓN PARA RAÍZ ----------------------- */

// La función calcula la raíz de índice entero second_number, de la base first_number
double root(double first_number, double second_number)
{
    // Casteo second_number a int y lo guardo en new_number
    int new_number = (int)(second_number);
    
    // Si second_number es igual a 0, o bien si first_number es negativo y new_number es par
    if ((second_number == 0) || ((first_number < 0) && (new_number % 2 == 0)))
    {
        // Imprimimos un mensaje de error
        printf("Error: Undefined Expression \n");

        // Retornamos 'OPERATION_ERROR' (-1)
        return OPERATION_ERROR;
    }

    // En caso contrario, retornamos first_number elevado a la potencia 1/new_number (equivalente a una raíz)
    return (pow(first_number, (1.0 / new_number)));
}


/* *****************************************************************
    *                 FUNCIÓN DE CONVERTIBILIDAD                  *
   ***************************************************************** */

// La función verifica si un double es convertible a int sin redondeo (su parte decimal es 0)
bool is_integer(double number)
{
    // Si el número double recibido es igual a su casteo a int, retornamos verdadero
    if (number == (int)number)
    {
        return true;
    }

    // Si no es el caso, retornamos falso, indicando que tiene parte decimal
    return false;
}
