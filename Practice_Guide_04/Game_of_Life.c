/* ************************************************************
    * NOTAS INICIALES *
   ************************************************************ */

/* 
Esta versión del código propone las siguientes modificaciones adicionales:
1. Un salto en la función que recibe el input del usuario, tal que si inserta un caracter inválido, pueda 
modificarlo sin que se termine el juego.
2. Generación aleatoria del tamaño de la retícula usando la función rand() de la librería <stdlib.h> y tomando la función time() 
de la librería time.h como su semilla.

TODO (1): Encontrar alguna forma de no usar un goto en la modificación 1 (no es buena práctica)
Observación: Traté de usar funciones recursivas, pero el mensaje "Type the amount of generations you want to advance (q to quit):"
se imprimía dos veces.


También intentamos usar la librería SDL2 para correr el programa en una ventana auxiliar, pero no pudimos terminar de configurarla.
TODO (2): Terminar de implementar la librería SDL2
*/


/* ************************************************************
    * CONFIGURACIÓN GENERAL *
   ************************************************************ */

/* --------------- LIBRERÍAS UTILIZADAS --------------- */

// Librería estándar de entrada y salida en C
#include <stdio.h>

// Librería para trabajar con booleanos (verdadero y falso)
#include<stdbool.h>

// Librería para usar la función rand()
#include <stdlib.h>

// Librería para usar la función time() como semilla de rand()
#include <time.h>

/* Librería gráfica
#include <SDL2/SDL.h> */


/* --------------- DIMENSIONES DEL JUEGO --------------- */

// Definimos el alto y ancho de la retícula del juego, ahora como variables globales
int HEIGHT;
int WIDTH;

/* --------------- VALIDEZ DE CARACTERES Y OPERACIONES --------------- */

// Definimos una macro para validar el caracter (c) insertado por el usuario
#define IS_VALID_DIGIT(c) ((c) >= '0' && (c) <= '9')

// Definimos una variable booleana global que verifica si se debe omitir la impresión de la retícula
bool skip_print = false;

/* --------------- PROTOTIPOS DE LAS FUNCIONES --------------- */

// La función lee los caracteres insertados por el usuario, hasta que presione Enter para confirmar o 'q' (o 'Q') para salir
int read_user_input(void);

/* La función calcula el número de generaciones que quiere insertar el usuario, actualizando la potencia de 10 por la que 
tiene que multiplicar cada dígito */ 
int compose_num(int current_num, int digit);

// La función inicializa la retícula con un tamaño aleatorio
void initialize_grid();

// La función imprime la retícula correspondiente a la generación actual
void print_grid(int grid[HEIGHT][WIDTH]);

/* La función genera una pestaña externa en la que se muestran las sucesivas generaciones
void draw_grid(SDL_Renderer *renderer, int grid[HEIGHT][WIDTH]); */

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
    // Inicializamos la semilla para los números aleatorios
    srand(time(NULL));

    // Generamos las dimensiones aleatorias de la retícula
    initialize_grid();

    /* --------------- INICIALIZACIÓN DE LA RETÍCULA --------------- */

    // Definimos un arrary para la retícula actual y otro para la retícula siguiente
    int current_grid[HEIGHT][WIDTH];
    int next_grid[HEIGHT][WIDTH];

    /* Inicializamos un contador de columnas en 0 y lo aumentamos en 1 al recorrer cada posición en una misma fila, 
    hasta llegar a la posición WIDTH-1 */
    for(int row = 0; row < HEIGHT; row++)
    {
        /* Copiamos cada posición de la retícula correspondiente a la siguiente generación en la misma posición
        de la retícula correspondiente a la generación actual */  
        for(int col = 0; col < WIDTH; col++)
        {
            // Inicializamos todas las posiciones en 0 (vacías)
            current_grid[row][col] = 0;
        }
    }
    
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
            // Si el caracter insertado por el usuario es válido, no se saltea la impresión
            if (skip_print == false)
            {
                // Imprimimos la retícula correspondiente a la generación actual
                print_grid(current_grid);

                // Hacemos dos saltos de línea para separar las generaciones
                printf("\n \n");
            }

            /* --------------- ACTUALIZACIÓN DE LA RETÍCULA --------------- */

            // Calculamos cómo se verá la retícula de la siguiente generación
            next_generation(current_grid, next_grid);

            /* Inicializamos un contador de columnas en 0 y lo aumentamos en 1 al recorrer cada posición en una misma fila, 
            hasta llegar a la posición WIDTH-1 */
            for(int row = 0; row < HEIGHT; row++)
            {
                /* Copiamos cada posición de la retícula correspondiente a la siguiente generación en la misma posición
                de la retícula correspondiente a la generación actual */  
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

    /* --------------- VERIFICACIÓN DEL INPUT --------------- */

    /* Creamos una etiqueta para saltar a este punto y volver a solicitar el número de generaciones en caso de que el caracter 
    insertado por el usuario sea inválido */
    ask_4_input:
    
    // Leemos los caracteres de entrada hasta que se presione Enter
    while ((user_digit = getchar()) != '\n')
    {
        // Verificamos si el caracter insertado por el usuario es válido (debe ser un dígito del 0 al 9)
        if (IS_VALID_DIGIT(user_digit))
        {
            // Si el caracter es válido, convertimos el dígito a entero y actualizamos el número de generaciones
            gen_num = compose_num(gen_num, user_digit - '0');

            // Seteamos la variable que impide la impresión de la retícula a falso
            skip_print = false;
        }

        // Si el usuario presiona 'q' o 'Q', retornamos -1 y termina el programa (no se imprimen más generaciones)
        else if ((user_digit == 'q') || (user_digit == 'Q'))
        {
            printf("Exiting the game... \n");
            return -1;
        }

        // Si el usuario presiona cualquier otro caracter
        else
        {
            // Imprimimos un mensaje de error
            printf("Invalid input. Please type only numbers or 'q' to quit. \n");
            
            // Seteamos la variable que impide la impresión de la retícula a verdadero
            skip_print = true;

            // Llamamos a la función que maneja entradas inválidas
            goto ask_4_input;
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
    * FUNCIÓN PARA GENERAR EL TAMAÑO ALEATORIO DE LA RETÍCULA *
   ************************************************************ */
  
// La función inicializa la retícula con un tamaño aleatorio
void initialize_grid()
{
    // Establecemos un rango aleatorio para las dimensiones de la retícula (entre 5 y 20)
    HEIGHT = (rand() % 16) + 5;
    WIDTH = (rand() % 16) + 5;

    // Imprimimos el tamaño generado
    printf("Generated grid size: %d x %d \n", HEIGHT, WIDTH);

    /// La función no retorna nada
    return;
}


/* ************************************************************
    * FUNCIÓN PARA IMPRIMIR LA RETÍCULA *
   ************************************************************ */

// La función imprime la retícula correspondiente a la generación actual
void print_grid(int grid[HEIGHT][WIDTH])
{
    // Inicializamos un contador de filas en 0 y lo aumentamos en 1 al terminar de recorrer cada fila
    for(int row = 0; row < HEIGHT; row++)
    {
        // --------------- IMPRESIÓN DE LÍNEA SUPERIOR ---------------

        // Inicializamos un contador de columnas en 0 y lo aumentamos en 1 al recorrer cada posición en una misma fila
        for(int col = 0; col < WIDTH; col++)
        {
            // Imprimimos la línea superior en cada posición de una fila, para todas las filas
            printf("+---");
        }

        // Cerramos la línea superior con un '+' al final de la fila y hacemos un salto de línea
        printf("+ \n");

        // --------------- IMPRESIÓN DE LAS CÉLULAS ---------------

        // Inicializamos un contador de columnas en 0 y lo aumentamos en 1 al recorrer cada posición en una misma fila
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

    // Inicializamos un contador de columnas en 0 y lo aumentamos en 1 al recorrer cada posición en una misma fila
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



/*

Intentamos usar usar la librería SDL2 para imprimir una retícula en una pestaña auxiliar y que se apreciara mejor, 
pero no pudimos terminar de configurar la librería SDL2 correctamente así que dejamos nuestros avances comentados.

Dimensiones de la ventana
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

Tamaño de cada célula en píxeles
const int CELL_SIZE = 20;  

--------------- ????? ---------------

    Ciclo del juego
    bool quit = false;
    SDL_Event e;

    Inicializamos SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    Crear ventana
    SDL_Window *window = SDL_CreateWindow("Conway's Game of Life",
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s \n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    Crear renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("Renderer could not be created! SDL_Error: %s \n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }


   ************************************************************
    * FUNCIÓN PARA IMPRIMIR LA RETÍCULA *
   ************************************************************

Función para dibujar la grilla en SDL
void draw_grid(SDL_Renderer *renderer, int grid[HEIGHT][WIDTH])
{
    for (int row = 0; row < HEIGHT; row++)
    {
        for (int col = 0; col < WIDTH; col++)
        {
            SDL_Rect cell;
            cell.x = col * CELL_SIZE;
            cell.y = row * CELL_SIZE;
            cell.w = CELL_SIZE;
            cell.h = CELL_SIZE;

            if (grid[row][col] == 1)
            {
                Célula viva (negro)
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
            } 
            else
            {
                Célula muerta (blanco)
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            SDL_RenderFillRect(renderer, &cell);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &cell);
        }
    }
}


   ************************************************************
    * FUNCIÓN PRINCIPAL *
   ************************************************************

La función principal imprime los mensajes en pantalla y llama a las otras funciones
int main(void)
{
    Inicializamos la semilla para los números aleatorios
    srand(time(NULL));

    Generamos las dimensiones aleatorias de la retícula
    initialize_grid();

    --------------- INICIALIZACIÓN DE LA RETÍCULA ---------------

    Definimos un array para la retícula actual y otro para la retícula siguiente
    int current_grid[HEIGHT][WIDTH];
    int next_grid[HEIGHT][WIDTH];

    Inicializamos todas las células en 0 (muertas)
    for(int row = 0; row < HEIGHT; row++)
    {
        for(int col = 0; col < WIDTH; col++)
        {
            current_grid[row][col] = 0;
        }
    }

    Inicializamos algunas células vivas para empezar
    current_grid[4][5] = 1;
    current_grid[5][5] = 1;
    current_grid[6][5] = 1;
    current_grid[7][6] = 1;
    current_grid[8][6] = 1;
    current_grid[10][8] = 1;
    current_grid[12][15] = 1;
    current_grid[14][15] = 1;

    Definimos una variable que guardará el número total de generaciones que quiere ejecutar el usuario
    int total_gens;

    Definimos una variable que contará el número de generaciones que se van ejecutando (desde el input del usuario)
    int current_gen;
  
    --------------- IMPRESIÓN DE LA RETÍCULA ---------------
    
    Imprimimos la generación actual hasta que el usuario presione 'q' (o 'Q') para salir o cualquier caracter inválido
    while (!quit && (total_gens = read_user_input()) != -1)
    {
        Inicializamos el contador de generaciones en 0 y lo aumentamos en 1 al terminar de imprimir cada generación,
        hasta imprimir todas las generaciones que indicó el usuario  
        for(current_gen = 0; current_gen < total_gens; current_gen++)
        {
            Manejo de eventos (ej: cerrar la ventana)
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                    break;
                }
            }

            Dibujar la generación actual
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);
            draw_grid(renderer, current_grid);
            SDL_RenderPresent(renderer);


            --------------- ACTUALIZACIÓN DE LA RETÍCULA ---------------

            Calculamos cómo se verá la retícula de la siguiente generación
            next_generation(current_grid, next_grid);

            Inicializamos un contador de filas en 0 y lo aumentamos en 1 al terminar de recorrer cada fila, hasta llegar a la 
            fila HEIGHT-1
            for(int row = 0; row < HEIGHT; row++)
            {
                Inicializamos un contador de columnas en 0 y lo aumentamos en 1 al recorrer cada posición en una misma fila, 
                hasta llegar a la posición WIDTH-1
                for(int col = 0; col < WIDTH; col++)
                {
                    Copiamos cada posición de la retícula correspondiente a la siguiente generación en la misma posición
                    de la retícula correspondiente a la generación actual
                    current_grid[row][col] = next_grid[row][col];
                }
            }
        }

        Pausar medio segundo entre generaciones
        SDL_Delay(500);  
    }

    Limpiar SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


*/