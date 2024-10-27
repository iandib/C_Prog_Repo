/* ************************************************************
    * CONFIGURACIÓN DEL ARCHIVO *
   ************************************************************ */

/* --------------- LIBRERÍAS UTILIZADAS --------------- */

// Librería estándar de entrada y salida en C
#include <stdio.h>

// Librería para trabajar con booleanos (verdadero y falso)
#include <stdbool.h>

// Librería para usar la función rand()
#include <stdlib.h>

// Librería para usar la función time() como semilla de rand()
#include <time.h>

// Librería para usar allegro
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

/* --------------- LLAMADA A HEADERS --------------- */

// Header correspondiente al archivo que recibe y procesa el input del usuario
#include "Front_End/get_input.h"

// Header correspondiente al archivo que imprime la retícula actual
#include "Back_End/print_grid.h"


/* ************************************************************
    * FUNCIÓN PRINCIPAL *
   ************************************************************ */

// La función principal imprime los mensajes en pantalla y llama a las otras funciones
int main(void)
{
    /* --------------- INICIALIZACIÓN DE LA RETÍCULA --------------- */

    // Llamamos a la función srand con la semilla time para generar números "aleatorios"
    srand(time(NULL));

    al_init();
    al_install_keyboard();

    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    // Definimos un arrary para la retícula actual y otro para la retícula siguiente
    int current_grid[HEIGHT][WIDTH] = {0};
    int next_grid[HEIGHT][WIDTH] = {0};

    // Definimos dos variables para ubicar a las células en el array correspondiente a la retícula
    int cell_row;
    int cell_col;

    // Definimos una variable para guardar la cantidad aleatoria de células vivas que habrá al inicio
    int alive_cells = (rand() % (HEIGHT * WIDTH));

    /* Inicializamos un contador de células vivas en 0 y lo aumentamos en 1 al iniciar una célula como viva, hasta llegar a la 
    cantidad aleatoria calculada anteriormente */
    for(int alive_cells_count = 0; alive_cells_count < alive_cells; alive_cells_count++)
    {
        // Nos ubicamos en una fila y columna aleatoria
        cell_row = (rand() % HEIGHT);
        cell_col = (rand() % WIDTH );

        // Inicializamos esa posición aleatoria con una célula viva
        current_grid[cell_row][cell_col] = 1;
    }
    
    // Definimos una variable que contará el número de generaciones que se van ejecutando (desde el input del usuario)
    int current_gen;
    int numero = 0;

    /* --------------- IMPRESIÓN DE LA RETÍCULA --------------- */
    
    // Imprimimos la generación actual hasta que el usuario presione 'q' (o 'Q') para salir o cualquier caracter inválido
    while(numero != -1)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            int numero = -1;

            // Detectar número presionado (0-9)
            if (ev.keyboard.keycode >= ALLEGRO_KEY_0 && ev.keyboard.keycode <= ALLEGRO_KEY_9) {
                numero = ev.keyboard.keycode - ALLEGRO_KEY_0;  // Convertir a número 0-9
            }

            if (numero != -1) {
                /* Inicializamos el contador de generaciones en 0 y lo aumentamos en 1 al terminar de imprimir cada generación,
                hasta imprimir todas las generaciones que indicó el usuario */  
                for(current_gen = 0; current_gen < numero; current_gen++)
                {
                    // Imprimimos la retícula correspondiente a la generación actual
                    print_grid(current_grid);

                    // Hacemos dos saltos de línea para separar las generaciones
                    printf("\n \n");

                    /* --------------- ACTUALIZACIÓN DE LA RETÍCULA --------------- */

                    // Calculamos cómo se verá la retícula de la siguiente generación
                    next_generation(current_grid, next_grid);

                    // Copiamos la retícula de la siguiente generación en la retícula actual
                    copy_grid(current_grid, next_grid);
                }
            }

            // Cerrar si se presiona ESC
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                numero = -1;
            }
        }
    }

    // Limpiar
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    // La función retorna 0 si todo funciona correctamente
    return 0;
}

