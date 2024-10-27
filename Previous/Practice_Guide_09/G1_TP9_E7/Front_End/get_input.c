/* *****************************************************************
    *                  CONFIGURACIÓN DEL ARCHIVO                  *
   ***************************************************************** */

/* ---------------------- HEADERS UTILIZADOS ------------------------ */

// Header correspondiente a este archivo
#include "get_input.h"

/* ---------------------- VARIABLES EXTERNAS ---------------------- */

// Declaramos el arreglo para almacenar los operadores
extern char operators[MAX_OPERATORS];

// Declaramos el arreglo de punteros a las funciones que realizan las operaciones
extern double (*operations[MAX_OPERATORS])(double, double);

// Definimos la flag para verificar si ambos operandos están listos
extern bool operands_ready;

/* ----------------- VARIABLES GLOBALES PRIVADAS ----------------- */

// Definimos una flag para controlar si ya se guardó el primer operando
static bool got_first_operand = false;

// Definimos una flag para controlar si el número ingresado tiene parte decimal
static bool is_float = false;

// Definimos una flag para controlar si el número insertado es negativo
static bool is_negative = false;

/* --------------- PROTOTIPOS DE FUNCIONES PRIVADAS --------------- */

// La función compone el número que quiere insertar el usuario a partir de los dígitos insertados
static void handle_number_input(double *num, unsigned char user_char, bool *got_first_operand, bool *operands_ready, bool is_float, int *float_pow, bool is_negative);

// La función convierte el número ingresado a negativo, en caso de ser necesario
static void handle_negative(double *operand, bool *received_num);

// La función compone el número que quiere insertar el usuario a partir de los dígitos insertados
static int handle_operator_input(unsigned char user_char, bool *got_first_operand, int *special_char_counter, int *action_char_counter);


/* *****************************************************************
    *                 FUNCIÓN PARA RECIBIR INPUT                  *
   ***************************************************************** */

// La función lee los caracteres insertados por el usuario, hasta que presione Enter para confirmar o 'E' para salir
int read_user_input(double *first_operand, double *second_operand, int *operator_index, double *result)
{
    /* ------------------- VARIABLES LOCALES ------------------- */

    // Definimos una variable que almacenará el último caracter ingresado por el usuario
    unsigned char user_char;

    // Definimos una flag para controlar si se ingresó un caracter
    bool got_char = false;

    // Definimos una variable para contar la cantidad de caracteres especiales (operadores o inválidos) ingresados
    int special_char_counter = 0;

    // Definimos una variable para contar la cantidad de caracteres de acción (para dar información o salir) ingresados
    int action_char_counter = 0;

    // Definimos una flag para validar la acción que quiere ejecutar el usuario
    bool is_exit_attempt = false;
    bool is_info_attempt = false;

    // Definimos una variable para registrar la posición decimal del último dígito ingresado tras '.' o ','
    int float_pow = 1;

    /* -------------------- INICIALIZACIÓN -------------------- */

    // Reinicio ambos operandos
    *first_operand = 0;
    *second_operand = 0;

    // Seteo el índice de operador a 'OPERATOR_ERROR' (-2)
    *operator_index = OPERATOR_ERROR;

    // Reseteamos la flag que verifica si ya se guardó el primer operando
    got_first_operand = false;

    // Reseteamos la flag que controla si el número ingresado tiene parte decimal
    is_float = false;

    // Reseteamos la flag que controla si ambos operandos están listos
    operands_ready = false;

    // Solicitamos la operación a realizar
    printf("Type any standard math operation (press 'E' to exit): ");

    /* --------------------- PROCESAMIENTO --------------------- */

    // Leemos los caracteres de entrada hasta que se presione Enter
    while ((user_char = getchar()) != '\n')
    {
        // Si el caracter ingresado es un dígito válido (del 0 al 9)
        if (IS_VALID_DIGIT(user_char))
        {
            // Activamos la flag que verifica si se ingresó un caracter
            got_char = true;

            // Manejamos la entrada del operando, verificando si es el segundo (posición 1) o el primero (posición 0)
            handle_number_input(got_first_operand ? second_operand : first_operand, user_char, &got_first_operand, &operands_ready, is_float, &float_pow, is_negative);

            // Manejamos el caso en el que el primer operando es negativo
            handle_negative(first_operand, &got_first_operand);
        }

        // Si el caracter ingresado es '.' o ',' (declara input con parte flotante)
        else if ((user_char == '.') || (user_char == ','))
        {
            // Activamos la flag que verifica si se ingresó un caracter
            got_char = true;

            // Activamos el flag para punto flotante
            is_float = true;
        }

        // Si el primer caracter ingresado es '~' (declara input negativo)
        else if ((user_char == '~') && (got_char == false))
        {
            // Activamos la flag que verifica si se ingresó un caracter
            got_char = true;

            // Activamos el flag para negativos
            is_negative = true;
        }

        // Si el caracter ingresado es un espacio vacío, lo ignoramos
        else if (user_char == ' ')
        {
            continue;
        }

        // Si el único caracter ingresado es 'I' o 'i', imprimimos información de las operaciones permitidas
        else if (((user_char == 'I') || (user_char == 'i')) && (got_char == false))
        {
            // Aumentamos el contador de caracteres de acción
            action_char_counter++;
            
            // Activamos la flag que valida la acción que quiere ejecutar el usuario
            is_info_attempt = true;
        }

        // Si el único caracter ingresado es 'E' o 'e'
        else if (((user_char == 'E') || (user_char == 'e')) && (got_char == false))
        {
            // Aumentamos el contador de caracteres de acción
            action_char_counter++;
            
            // Activamos la flag que valida la acción que quiere ejecutar el usuario
            is_exit_attempt = true;
        }

        // Si el caracter ingresado es otro
        else
        {
            // Activamos la flag que detectar si se ingresaron caracteres
            got_char = true;

            // Aumentamos el contador de caracteres operadores o inválidos ingresados
            special_char_counter++;

            // Manejamos la entrada, guardando el índice correspondiente al operador ingresado o un error
            *operator_index = handle_operator_input(user_char, &got_first_operand, &special_char_counter, &action_char_counter);
        }
    }

    /* ----------------- INSTANCIAS ESPECIALES ----------------- */

    // Si fue un intento de mostrar información (se ingresó únicamente 'I' o 'i')
    if (is_info_attempt && !got_char && (action_char_counter == 1))
    {
        // Guardamos 0 como índice default de operador al no trabajar ninguna operación
        *operator_index = 0;

        // Imprimimos los mensajes correspondietes
        printf("Supported operations:\n");
        printf("\t + : Addition \n");
        printf("\t - : Subtraction \n");
        printf("\t * : Multiplication \n");
        printf("\t / : Division \n");
        printf("\t ^ : Exponentiation \n");
        printf("\t r : Root \n");
        printf("To indicate the first number is negative, use '~' \n");
    }

    // Si fue un intento de salir (se ingresó únicamente 'E' o 'e')
    if (is_exit_attempt && !got_char && (action_char_counter == 1))
    {
        // Guardamos 0 como índice default de operador al no trabajar ninguna operación
        *operator_index = 0;

        // Imprimimos el mensaje correspondiente
        printf("Exiting the calculator... \n");

        // Retornamos 'EXIT_REQUEST' (-1)
        return EXIT_REQUEST;
    }

    // Retornamos 0 si todo funciona correctamente
    return 0;
}


/* *****************************************************************
    *            FUNCIÓN PARA MANEJAR INPUT DE NÚMEROS            *
   ***************************************************************** */

// La función compone el número que quiere insertar el usuario a partir de los dígitos insertados
static void handle_number_input(double *num, unsigned char user_char, bool *got_first_operand, bool *operands_ready, bool is_float, int *float_pow, bool is_negative)
{
    // Si no se ingresó '.' o ',' para agregar una parte decimal
    if (!is_float)
    {
        // Multiplicamos el número actual por 10 y sumamos el nuevo dígito convertido a entero (restando '0')
        *num = (*num * 10) + (user_char - '0');
    }

    // En caso contrario
    else
    {
        /* Al número actual le sumamos el decimal correspondiente al último dígito ingresado, para lo cual convertimos el dígito a entero
        (restando '0') y lo dividimos entre la potencia de 10 correspondiente */
        *num = *num + ((user_char - '0')/power(10, *float_pow));

        // Incrementamos float_pow, avanzando de posición decimal en la que se sumará el próximo dígito
        (*float_pow)++;
    }

    // Si es la segunda vez que se llama a la función
    if (*got_first_operand)
    {
        // Activamos la flag que controla si ambos operandos están listos
        *operands_ready = true;
    }

    // No retornamos nada
    return;
}


/* *****************************************************************
    *               FUNCIÓN PARA MANEJAR NEGATIVOS                *
   ***************************************************************** */

// La función convierte el número ingresado a negativo, en caso de ser necesario
static void handle_negative(double *operand, bool *received_num)
{
    // Si se ingresa '~' para indicar que el número es negativo y ya se terminó de escribir el número
    if (is_negative && *received_num)
    {
        // Hacemos la conversión correspondiente
        *operand = *operand * (-1);

        // Reseteamos la flag que controla si el número insertado es negativo
        is_negative = false;
    }

    // No retornamos nada
    return;
}


/* *****************************************************************
    *           FUNCIÓN PARA MANEJAR INPUT DE OPERADORES          *
   ***************************************************************** */

// La función compone el número que quiere insertar el usuario a partir de los dígitos insertados
static int handle_operator_input(unsigned char user_char, bool *got_first_operand, int *special_char_counter, int *action_char_counter)
{
    // Definimos una variable para guardar el índice correspondiente al operador ingresado
    int operator_index = 0;

    // Iteramos sobre el arreglo de operadores válidos, inicializando un índice en 0 y aumentándolo en 1 al recorrer cada posición
    for (int index = 0; index < MAX_OPERATORS; index++)
    {
        // Si el caracter ingresado coincide con un operador del arreglo
        if (user_char == operators[index])
        {
            // Activamos la flag que controla si se guardó el primer operando
            *got_first_operand = true;

            // Reseteamos la flag que controla si el número ingresado tiene parte decimal
            is_float = false;

            // Retornamos el índice correspondiente a la posición del operador ingresado
            operator_index = index;
        }
    }

    // Si solo se ingresó un único caracter especial, es un operador, por lo que retornamos su índice
    if ((*special_char_counter == 1) && (*action_char_counter == 0))
    {
        return operator_index;
    }

    // En cualquier otro caso, retornamos 'OPERATOR_ERROR' (-2)
    return OPERATOR_ERROR;
}
