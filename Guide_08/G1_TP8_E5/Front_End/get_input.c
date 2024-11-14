/* ************************************************************
    * CONFIGURACIÓN DEL ARCHIVO *
   ************************************************************ */

/* --------------- LLAMADA A HEADERS --------------- */

#include "get_input.h"

/* --------------- PROTOTIPOS DE FUNCIONES --------------- */

/* La función calcula el número de generaciones que quiere insertar el usuario, actualizando la potencia de 10 por la que 
tiene que multiplicar cada dígito */ 
static int compose_num(int current_num, int digit);

/* --------------- VALIDEZ DE CARACTERES --------------- */

// Definimos una flag para validar si el usuario insertó un caracter inválido
bool syntax_error = false;


/* ************************************************************
    * FUNCIÓN PARA RECIBIR EL INPUT DEL USUARIO *
   ************************************************************ */

// La función lee los caracteres insertados por el usuario, hasta que presione Enter para confirmar o 'q' (o 'Q') para salir
int read_user_input(void)
{
    // Definimos una variable que almacenará el último caracter ingresado por el usuario
    unsigned char user_digit;
    
    // Definimos una variable que guardará el número de generaciones ingresado por el usuario y la inicializamos en 0
    int gen_num = 0;

    // Reseteamos el flag que verifica si el usuario insertó un caracter no válido
    syntax_error = false;

    // Definimos una variable para llevar el control de si el usuario presionó 'q' o 'Q'
    bool quit_flag = false;

    // Solicitamos el número de generaciones
    printf("Type the amount of generations you want to advance (q to quit): ");

    /* --------------- RECEPCIÓN DEL INPUT --------------- */
    
    // Leemos los caracteres de entrada hasta que se presione Enter
    while ((user_digit = getchar()) != '\n')
    {
        // Si el caracter insertado por el usuario es válido (dígito del 0 al 9)
        if (IS_VALID_DIGIT(user_digit))
        {
            // Convertimos el dígito a entero y actualizamos el número de generaciones
            gen_num = compose_num(gen_num, user_digit - '0');
        }

        // Si el usuario presiona 'q' o 'Q', activamos el flag de salida
        else if ((user_digit == 'q') || (user_digit == 'Q'))
        {
            quit_flag = true;
        }

        // Si el usuario presiona cualquier otro caracter, activamos el flag de error de sintaxis
        else
        {
            syntax_error = true;
        }
    }

    /* --------------- MANEJO DEL INPUT --------------- */

    /* Si el flag de salida está activado, no se insertaron más caracteres (no se activó el flag de error de sintaxis) y 
    no se insertó un número de generaciones, finalizamos el programa */
    if (quit_flag && !syntax_error && (gen_num == 0))
    {
        printf("Exiting the game... \n");
        return EXIT_REQUEST;
    }

    /* Si se activó el flag de error de sintaxis o bien si se activó el flag de salida y, a la vez, se insertó un número
    de generaciones */
    if (syntax_error || (quit_flag && (gen_num != 0)))
    {
        // Imprimimos un mensaje de error
        printf("Invalid input. Please type only numbers or 'q' to quit. \n");

        // Volvemos a solicitar el input, sin reiniciar la generación
        return read_user_input();
    }

    /* Si se presiona Enter sin ingresar un número de generaciones (la variable sigue estando en 0), retornamos 1 
    para avanzar una generación por defecto */
    if (gen_num == 0)
    {
        return 1;
    }

    // Si la cantidad de generaciones ingresada es válida, retornamos el número correspondiente
    return gen_num;
}


/* ************************************************************
    * FUNCIÓN PARA COMPONER UN NÚMERO A PARTIR DE DÍGITOS *
   ************************************************************ */

/* La función calcula el número de generaciones que quiere insertar el usuario, actualizando la potencia de 10 por la que 
tiene que multiplicar cada dígito */ 
static int compose_num(int current_num, int digit)
{
    // Multiplicamos el número actual por 10 y sumamos el nuevo dígito
    return (current_num * 10) + digit;
}
