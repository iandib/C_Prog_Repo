/* ************************************************************
    * NOTAS INICIALES *
   ************************************************************ */

/*
Escribí los mensajes en inglés para no tener conflictos con los caracteres que no vienen incluidos en la tabla ASCII.

--------------- IMPRESIÓN DE CADA POSICIÓN: DESFACE ---------------

En matrices impares el centro está definido por una sola celda, por lo que la distancia desde los bordes hasta el centro es exactamente igual 
a la distancia máxima (max_dist - dist = 0). Por eso, sumo 1 para que las celdas de los bordes inicien en este valor. 

En cambio, en matrices pares el centro ocupa un rango de dos celdas, lo que introduce un desfase. Al sumar 2 compenso este desfase, logrando 
que las celdas en los bordes también comiencen en 1.
*/


/* ************************************************************
    * CONFIGURACIÓN GENERAL *
   ************************************************************ */

/* --------------- LIBRERÍAS UTILIZADAS --------------- */

// Librería estándar de entrada y salida en C
#include <stdio.h>

/* --------------- PARÁMETROS Y VARIABLES --------------- */

// Defino una macro para validar el caracter (c) insertado por el usuario
#define IS_VALID_DIGIT(c) ((c) >= '0' && (c) <= '9')

// Defino una macro para validar si el tamaño de la dimensión está en el rango permitido
#define IS_INVALID_SIZE(s) (((s) < 1) || ((s) > 20))

// Defino una variable que tendrá la dimensión de la pirámide que quiere el usuario
int size = 0;

/* --------------- PROTOTIPOS DE LAS FUNCIONES --------------- */

// La función lee los caracteres insertados por el usuario y guarda la dimensión de la pirámide que quiere insertar
int read_user_input(void);

// La función calcula el número que quiere insertar el usuario, actualizando la potencia de 10 por la que tiene que multiplicar cada dígito
int compose_num(int current_num, int digit);

// La función calcula el valor absoluto de un número (la uso porque no nos dejan usar la librería math.h)
int calc_abs(int num);

// La función imprime la pirámide dada su dimensión (n)
void pyramid(int n);

// La función calcula la distancia máxima de cada celda (row, col) al centro de la pirámide
int calc_dist(int n, int row, int col);

// La función devuelve el índice central de la matriz (o el rango si n es par)
void find_center(int n, int* center_start, int* center_end);


/* ************************************************************
    * FUNCIÓN PRINCIPAL *
   ************************************************************ */

int main()
{
    /* Llamo a la función que recibe la dimensión de la pirámide, si devuelve -1 significa que hubo un error y termino la ejecución
    retornando 1 */
    if (read_user_input() == -1)
    {
        return 1;
    }   

    // Si no hubo errores, llamo a la función para imprimir la pirámide y retorno 0
    else
    {
        pyramid(size);
        return 0;
    }
}


/* ************************************************************
    * FUNCIÓN PARA RECIBIR EL INPUT DEL USUARIO *
   ************************************************************ */

// La función lee los caracteres insertados por el usuario y guarda la dimensión de la pirámide que quiere insertar
int read_user_input(void)
{
    /* --------------- INICIALIZACIÓN DE VARIABLES --------------- */

    // Defino una variable que almacenará el último caracter ingresado por el usuario
    unsigned char user_digit;

    // Solicito al usuario el tamaño de la pirámide
    printf("Enter the size of the pyramid: ");

    /* --------------- MANEJO DEL INPUT --------------- */

    // Leo los caracteres de entrada hasta que se presione Enter
    while ((user_digit = getchar()) != '\n')
    {
        // Si el caracter insertado por el usuario es válido (dígito del '0' al '9')
        if (IS_VALID_DIGIT(user_digit))
        {
            // Convierto el dígito a entero y lo acumulo en la dimensión de la pirámide
            size = compose_num(size, user_digit - '0');

            // Si el tamaño insertado está fuera del rango permitido, retorno -1 e imprimo un mensaje de error
            if (IS_INVALID_SIZE(size))
            {
                printf("Invalid input. Please enter a number between 1 and 25. \n");
                return -1;
            }
        }

        // Si el caracter insertado no es válido, retorno -1 e imprimo un mensaje de error
        else
        {
            printf("Invalid input. Please type only numbers. \n");
            return -1;
        }
    }

    // Si no hubo errores, retorno 0
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
    * FUNCIÓN PARA CALCULAR VALOR ABSOLUTO *
   ************************************************************ */

// La función calcula el valor absoluto de un número (la uso porque no nos dejan usar la librería math.h)
int calc_abs(int num)
{
    return (num > 0) ? num : -num;
}


/* ************************************************************
    * FUNCIÓN PARA IMPRIMIR LA PIRÁMIDE *
   ************************************************************ */

// La función imprime la pirámide dada su dimensión (n)
void pyramid(int n)
{
    // Defino una variable para calcular la distancia máxima que puede tener una celda a su centro
    int max_dist = ((n - 1) / 2);

    // Inicializo el contador de filas en 1 y lo aumentamos en 1 al terminar de imprimir cada fila, hasta completar toda la pirámide
    for (int row = 1; row <= n; row++)
    {
        // Inicializo el contador de columnas en 1 y lo aumentamos en 1 al terminar de imprimir cada posición en una fila, hasta completar toda la fila
        for (int col = 1; col <= n; col++)
        {
            // Calculo la distancia de la celda actual al centro de la pirámide
            int dist = calc_dist(n, row, col);
            
            /* --------------- IMPRESIÓN DE CADA POSICIÓN --------------- */

            // La explicación del ajuste está en las notas iniciales

            if (n % 2 == 0)
            {
                // Si la pirámide tiene dimensiones pares, sumo 2 para hacer el ajuste de los bordes
                printf("%d ", (max_dist - dist + 2));
            }

            else
            {
                // Si la pirámide tiene dimensiones impares, sumo 1 para hacer el ajuste de los bordes
                printf("%d ", (max_dist - dist + 1));
            }
        }

        // Hago u nsalto de línea para cambiar de fila
        printf("\n");
    }

    // La función no retorna nada
    return;
}


/* ************************************************************
    * FUNCIÓN PARA CALCULAR DISTANCIA AL CENTRO *
   ************************************************************ */

// La función calcula la distancia máxima de cada celda (row, col) al centro de la pirámide
int calc_dist(int n, int row, int col)
{
    // Defino dos variables para guardar la posición del centro de la pirámide (donde inicia y donde termina)
    int center_start, center_end;

    /* Llamo a la función find_center para encontrar el centro de la pirámide, le paso un puntero a las variables que acabo de definir
    para poder modificarlas directamente */
    find_center(n, &center_start, &center_end);

    /* --------------- DISTANCIA A LA FILA DEL CENTRO --------------- */

    // Me quedo con la mayor distancia (valor absoluto) entre la fila actual y la fila correspondiente al inicio o fin del centro
    int dist_row = (calc_abs(row - center_start) > calc_abs(row - center_end)) ?
                    calc_abs(row - center_start) : 
                    calc_abs(row - center_end);

    /* --------------- DISTANCIA A LA COLUMNA DEL CENTRO --------------- */

    // Me quedo con la mayor distancia (valor absoluto) entre la columna actual y la columna correspondiente al inicio o fin del centro
    int dist_col = (calc_abs(col - center_start) > calc_abs(col - center_end)) ?
                    calc_abs(col - center_start) :
                    calc_abs(col - center_end);

    /* --------------- SELECCIÓN DE DISTANCIA MÁXIMA --------------- */

    // Retorno la mayor distancia al centro (entre filas y columnas) desde la celda actual
    return (dist_row > dist_col) ? dist_row : dist_col;
}


/* ************************************************************
    * FUNCIÓN PARA DETECTAR EL CENTRO DE LA PIRÁMIDE *
   ************************************************************ */

// La función devuelve el índice central de la matriz (o el rango si n es par)
void find_center(int n, int* center_start, int* center_end)
{
    // Si n es par, el centro está en un rango de dos posiciones
    if (n % 2 == 0)
    {
        // Tomo el inicio del centro como el entero que resulta de dividir la dimensión de la pirámide entre 2
        *center_start = (n / 2);

        // Tomo el fin del centro como la posición siguiente a la del inicio
        *center_end = *center_start + 1;
    }

    // Si n es impar, el centro está en una sola posición, es decir que el inicio y el fin son coincidentes
    else
    {
        // Esta posición se calcula como el siguiente a la división entre la dimensión de la pirámide y 2
        *center_start = *center_end = ((n / 2) + 1);
    }

    // La función no retorna nada porque, al usar punteros, modifica las variables originales que guardan la posición del centro
    return;
}


