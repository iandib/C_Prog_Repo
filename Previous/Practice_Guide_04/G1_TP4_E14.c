/* ************************************************************
    * NOTAS INICIALES *
   ************************************************************ */

/*
Escribimos los mensajes en inglés para no tener conflictos con los caracteres que no vienen incluidos en la tabla ASCII.

Es muy importante recordar que los arrays en C empiezan en 0 y llegan hasta el N-1.

Al buscar cómo retornar un array en una función para asignarlo a otro, encontré que en C, al pasar un array a una función, realmente le 
estamos pasando el puntero a ese array, por lo que cualquier cambio que se le haga al array de la función afecta directamente al original. 
Por esto, no es necesario que la función next_generation retorne el array next_grid.

Esta versión del código cumple con todas las funcionalidades que pide el ejercicio, pero no propone adicionales.
*/


/* ************************************************************
    * CONFIGURACIÓN GENERAL *
   ************************************************************ */

/* --------------- LIBRERÍAS UTILIZADAS --------------- */

// Librería estándar de entrada y salida en C
#include <stdio.h>

/* --------------- DIMENSIONES DEL JUEGO --------------- */

// Definimos el alto y ancho de la retícula del juego
#define HEIGHT 15
#define WIDTH 20

// Revisamos que la retícula se pueda imprimir
#if ((HEIGHT <= 0) || (WIDTH <= 0))
    #error Invalid dimensions: must be greater than 0

// Revisamos que la retícula no se vea demasiado chica
#elif ((HEIGHT > 50) || (WIDTH > 50) || (HEIGHT * WIDTH > 1000))
    #warning Unrecommended dimensions: output will be hard to visualize

#endif

/* --------------- VALIDEZ DE CARACTERES --------------- */

// Definimos una macro para validar el caracter (c) insertado por el usuario
#define IS_VALID_DIGIT(c) ((c) >= '0' && (c) <= '9')

/* --------------- PROTOTIPOS DE LAS FUNCIONES --------------- */

// La función lee los caracteres insertados por el usuario, hasta que presione Enter para confirmar o 'q' (o 'Q') para salir
int read_user_input(void);

/* La función calcula el número de generaciones que quiere insertar el usuario, actualizando la potencia de 10 por la que 
tiene que multiplicar cada dígito */ 
int compose_num(int current_num, int digit);

// La función imprime la retícula correspondiente a la generación actual
void print_grid(int grid[HEIGHT][WIDTH]);

// La función cuenta cuántos vecinos vivos tiene la célula en la posición (row, col) de la generación actual
int count_live_neighbors(int grid[HEIGHT][WIDTH], int row, int col);

// La función calcula la siguiente generación que debe imprimirse a partir de la generación actual y de las reglas del juego
void next_generation(int current_grid[HEIGHT][WIDTH], int next_grid[HEIGHT][WIDTH]);


/* ************************************************************
    * FUNCIÓN PRINCIPAL *
   ************************************************************ */

// La función principal imprime los mensajes en pantalla y llama a las otras funciones
int main(void)
{
    /* --------------- INICIALIZACIÓN DE LA RETÍCULA --------------- */

    // Definimos un arrary para la retícula actual y otro para la retícula siguiente
    int current_grid[HEIGHT][WIDTH] = {0};
    int next_grid[HEIGHT][WIDTH] = {0};
    
    // Inicializamos algunas células vivas para empezar
    current_grid[4][5] = 1;
    current_grid[5][5] = 1;
    current_grid[6][5] = 1;
    current_grid[7][6] = 1;
    current_grid[8][6] = 1;
    current_grid[10][8] = 1;
    current_grid[12][15] = 1;
    current_grid[14][15] = 1;

    // Definimos una variable que guardará el número total de generaciones que quiere ejecutar el usuario
    int total_gens;
    
    // Definimos una variable que contará el número de generaciones que se van ejecutando (desde el input del usuario)
    int current_gen;

    /* --------------- IMPRESIÓN DE LA RETÍCULA --------------- */
    
    // Imprimimos la generación actual hasta que el usuario presione 'q' (o 'Q') para salir o cualquier caracter inválido
    while((total_gens = read_user_input()) != -1)
    {
        /* Inicializamos el contador de generaciones en 0 y lo aumentamos en 1 al terminar de imprimir cada generación,
        hasta imprimir todas las generaciones que indicó el usuario */  
        for(current_gen = 0; current_gen < total_gens; current_gen++)
        {
            // Imprimimos la retícula correspondiente a la generación actual
            print_grid(current_grid);

            // Hacemos dos saltos de línea para separar las generaciones
            printf("\n \n");

            /* --------------- ACTUALIZACIÓN DE LA RETÍCULA --------------- */

            // Calculamos cómo se verá la retícula de la siguiente generación
            next_generation(current_grid, next_grid);

            /* Inicializamos un contador de filas en 0 y lo aumentamos en 1 al terminar de recorrer cada fila, hasta llegar a la 
            fila HEIGHT-1 */
            for(int row = 0; row < HEIGHT; row++)
            {
                /* Inicializamos un contador de columnas en 0 y lo aumentamos en 1 al recorrer cada posición en una misma fila, 
                hasta llegar a la posición WIDTH-1 */
                for(int col = 0; col < WIDTH; col++)
                {
                    /* Copiamos cada posición de la retícula correspondiente a la siguiente generación en la misma posición
                    de la retícula correspondiente a la generación actual */  
                    current_grid[row][col] = next_grid[row][col];
                }
            }
        }
    }

    return 0;
}


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

    // Solicitamos el número de generaciones
    printf("Type the amount of generations you want to advance (q to quit): ");

    /* --------------- VERFICIACIÓN DEL INPUT --------------- */

    // Leemos los caracteres de entrada hasta que se presione Enter
    while ((user_digit = getchar()) != '\n')
    {
        // Verificamos si el caracter insertado por el usuario es válido (debe ser un dígito del 0 al 9)
        if (IS_VALID_DIGIT(user_digit))
        {
            // Si el caracter es válido, convertimos el dígito a entero y actualizamos el número de generaciones
            gen_num = compose_num(gen_num, user_digit - '0');
        }

        // Si el usuario presiona 'q' o 'Q', retornamos -1 y termina el programa (no se imprimen más generaciones)
        else if ((user_digit == 'q') || (user_digit == 'Q'))
        {
            printf("Exiting the game... \n");
            return -1;
        }

        // Si el usuario presiona cualquier otro caracter, también retornamos -1 e imprimimos un mensaje de error
        else
        {
            printf("Invalid input. Please type only numbers or 'q' to quit. \n");
            return -1;
        }
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
int compose_num(int current_num, int digit)
{
    // Multiplicamos el número actual por 10 y sumamos el nuevo dígito
    return (current_num * 10) + digit;
}


/* ************************************************************
    * FUNCIÓN PARA IMPRIMIR LA RETÍCULA *
   ************************************************************ */

// La función imprime la retícula correspondiente a la generación actual
void print_grid(int grid[HEIGHT][WIDTH])
{
    /* Inicializamos un contador de filas en 0 y lo aumentamos en 1 al terminar de recorrer cada fila, hasta llegar a la 
    fila HEIGHT-1 */
    for(int row = 0; row < HEIGHT; row++)
    {
        // --------------- IMPRESIÓN DE LÍNEA SUPERIOR ---------------

        /* Inicializamos un contador de columnas en 0 y lo aumentamos en 1 al recorrer cada posición en una misma fila, 
        hasta llegar a la posición WIDTH-1 */
        for(int col = 0; col < WIDTH; col++)
        {
            // Imprimimos la línea superior en cada posición de una fila, para todas las filas
            printf("+---");
        }

        // Cerramos la línea superior con un '+' al final de la fila y hacemos un salto de línea
        printf("+ \n");

        // --------------- IMPRESIÓN DE LAS CÉLULAS ---------------

        /* Inicializamos un contador de columnas en 0 y lo aumentamos en 1 al recorrer cada posición en una misma fila, 
        hasta llegar a la posición WIDTH-1 */
        for(int col = 0; col < WIDTH; col++)
        {
            // Separamos cada posición con un delimitador de columna '|'
            printf("| ");

            // Si la célula de la posición actual está viva (su valor es 1), imprimimos un '*'
            if(grid[row][col] == 1)
            {
                printf("* ");
            }

            // Si está vacía (su valor es 0), imprimimos un espacio vacío
            else
            {
                printf("  ");
            }
        }

        // Cerramos la fila con un delimitador final '|'
        printf("| \n");
    }

    // --------------- IMPRESIÓN DE LÍNEA INFERIOR ---------------

    /* Inicializamos un contador de columnas en 0 y lo aumentamos en 1 al recorrer cada posición en una misma fila, 
    hasta llegar a la posición WIDTH-1 */
    for(int col = 0; col < WIDTH; col++)
    {
        // Imprimimos la línea inferior en cada posición de la fila, únicamente para la última fila
        printf("+---");
    }

    // Cerramos la línea inferior con un '+' al final de la fila y hacemos un salto de línea
    printf("+ \n");

    // La función no retorna nada
    return;
}


/* ************************************************************
    * FUNCIÓN PARA CONTAR LOS VECINOS VIVOS DE UNA CÉLULA *
   ************************************************************ */

// La función cuenta cuántos vecinos vivos tiene la célula en la posición (row, col) de la retícula actual
int count_live_neighbors(int grid[HEIGHT][WIDTH], int row, int col)
{
    // Definimos una variable que almacenará el número de vecinos vivos
    int live_neighbors = 0;
    // Definimos una variable que almacenará el desplazamiento en una misma columna desde la posición (row, col)
    int row_displacement;
    // Definimos una variable que almacenará el desplazamiento en una misma fila desde la posición (row, col)
    int col_displacement;

    // --------------- ANÁLISIS DE ÁREA (3X3) ALREDEDOR DE LA CÉLULA ---------------

    // Recorremos las tres columnas que van desde 1 lugar a la izquierda de (row, col) hasta 1 lugar a su derecha
    for(row_displacement = -1; row_displacement <= 1; row_displacement++)
    {
        // Y repetimos lo anterior para las tres filas que van desde 1 lugar abajo de (row, col) hasta 1 lugar arriba suyo
        for(col_displacement = -1; col_displacement <= 1; col_displacement++)
        {
            // Si estamos en la posición actual (la célula misma), la omitimos
            if(row_displacement == 0 && col_displacement == 0)
            {
                continue;
            }

            // --------------- CONTADOR DE CÉLULAS VIVAS ---------------

            // Calculamos las coordenadas de cada célula vecina (se actualiza con cada valor de x e y en el recorrido de 3x3)
            int neighbor_row = row + row_displacement;
            int neighbor_col = col + col_displacement;

            /* Verificamos si las coordenadas de la célula vecina están dentro de los límites de la retícula (desde la posición 0
            hasta la posición N-1) */
            if((neighbor_row >= 0) && (neighbor_row < HEIGHT) && (neighbor_col >= 0) && (neighbor_col < WIDTH))
            {
                /* Si la célula vecina está viva (el valor de la posición (neighbor_row, neighbor_col) de la retícula es 1), 
                aumentamos el contador de células vivas en 1 */
                if(grid[neighbor_row][neighbor_col] == 1)
                {
                    live_neighbors++;
                }
            }
        }
    }

    // Retornamos el número total de vecinos vivos
    return live_neighbors;
}


/* ************************************************************
    * FUNCIÓN PARA CALCULAR LA SIGUIENTE GENERACIÓN *
   ************************************************************ */

// La función calcula la siguiente generación que debe imprimirse a partir de la generación actual y de las reglas del juego
void next_generation(int current_grid[HEIGHT][WIDTH], int next_grid[HEIGHT][WIDTH])
{
    // --------------- ANÁLISIS DE TODAS LAS POSICIONES EN LA RETÍCULA ---------------

    /* Inicializamos un contador de filas en 0 y lo aumentamos en 1 al terminar de recorrer cada fila, hasta llegar a la 
    fila HEIGHT-1 */
    for(int row = 0; row < HEIGHT; row++)
    {
        /* Inicializamos un contador de columnas en 0 y lo aumentamos en 1 al recorrer cada posición en una misma fila, 
        hasta llegar a la posición WIDTH-1 */
        for(int col = 0; col < WIDTH; col++)
        {
            // Contamos cuántos vecinos vivos tiene la célula en la posición (row, col)
            int live_neighbors = count_live_neighbors(current_grid, row, col);

            // --------------- APLICACIÓN DE LAS REGLAS DEL JUEGO ---------------

            // Si la célula en la posición (row, col) está viva (su valor es 1)
            if(current_grid[row][col] == 1)
            {
                // Si tiene menos de 2 vecinos vivos, muere por subpoblación (su valor pasa a ser 0)
                if(live_neighbors < 2)
                {
                    next_grid[row][col] = 0;
                }
                // Si tiene más de 3 vecinos vivos, muere por sobrepoblación (su valor pasa a ser 0)
                else if(live_neighbors > 3)
                {
                    next_grid[row][col] = 0;
                }
                // Si tiene exactamente 2 o 3 vecinos, sobrevive (su valor se mantiene en 1)
                else
                {
                    next_grid[row][col] = 1;
                }
            }

            // Si, en cambio, la posición (row, col) está vacía (su valor es 0)
            else
            {
                // Si tiene exactamente 3 vecinos, nace una célula (su valor pasa a ser 1)
                if(live_neighbors == 3)
                {
                    next_grid[row][col] = 1;
                }
                // En cualquier otro caso, la posición sigue vacía (su valor se mantiene en 0)
                else
                {
                    next_grid[row][col] = 0;
                }
            }
        }
    }

    // No es necesario que la función retorne las actualizaciones porque estas ya se guardan en el array original
    return;
}
