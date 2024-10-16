/* *****************************************************************
    *                   CONFIGURACIÓN DEL HEADER                   *
   ***************************************************************** */

//Nos aseguramos de que el Header solo se incluya una vez 
#ifndef OPERATE
#define OPERATE

/* ---------------------- LIBRERÍAS UTILIZADAS ---------------------- */

// Librería estándar de entrada y salida en C
#include <stdio.h>

// Librería para trabajar con booleanos (verdadero y falso)
#include <stdbool.h>

// Librería para trabajar con funciones matemáticas avanzadas
#include <math.h>

/* -------------------------- CONSTANTES -------------------------- */

// Definimos el número máximo de operadores
#define MAX_OPERATORS 6

// Definimos el número máximo de operandos
#define MAX_OPERANDS 2

// Definimos una constante de error al realizar la operación
#define OPERATION_ERROR -1

/* --------------- PROTOTIPOS DE FUNCIONES PÚBLICAS --------------- */

// La función devuelve la suma de first_number y second_number
double add(double first_number, double second_number);

// La función devuelve la diferencia entre first_number y second_number
double subtract(double first_number, double second_number);

// La función devuelve el producto de first_number y second_number
double multiply(double first_number, double second_number);

// La función devuelve el cociente entre first_number y second_number
double divide(double first_number, double second_number);

// La función eleva first_number a la potencia entera que indica second_number
double power(double first_number, double second_number);

// La función calcula la raíz de índice entero second_number, de la base first_number
double root(double first_number, double second_number);

// La función verifica si un double es convertible a int sin redondeo
bool is_integer(double number);

#endif
