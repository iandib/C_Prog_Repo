/* *****************************************************************
    *                  CONFIGURACIÓN DEL HEADER                   *
   ***************************************************************** */

// Nos aseguramos de que el Header solo se incluya una vez 
#ifndef GET_INPUT
#define GET_INPUT

/* --------------------- LIBRERÍAS UTILIZADAS --------------------- */

// Librería estándar de entrada y salida en C
#include <stdio.h>

// Librería para trabajar con booleanos (verdadero y falso)
#include <stdbool.h>

/* ---------------------- HEADERS UTILIZADOS ------------------------ */

// Header correspondiente al archivo que realiza las operaciones matemáticas
#include "../Back_End/operate.h"

/* ---------------------- MACROS Y CONSTANTES ---------------------- */

// Definimos una macro para validar el caracter (c) insertado por el usuario
#define IS_VALID_DIGIT(c) ((c) >= '0' && (c) <= '9')

// Definimos una constante para indicar que el usuario desea salir
#define EXIT_REQUEST -1

// Definimos una constante para indicar que no se insertó un operador válido
#define OPERATOR_ERROR -2

/* --------------- PROTOTIPOS DE FUNCIONES PÚBLICAS --------------- */

// La función lee los caracteres insertados por el usuario, hasta que presione Enter para confirmar o 'ESC' para salir
int read_user_input(double *first_operand, double *second_operand, int *operator_index, double *result);

#endif
