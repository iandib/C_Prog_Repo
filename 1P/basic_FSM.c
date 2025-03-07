#include <stdio.h>

// Definición de los estados
enum { S1, S2, S3 };
char estado = S1;  // La FSM empieza en el estado S1

char runFSM(char in) {
    // FSM en base al estado actual y la entrada
    switch (estado) {
        case S1:
            if (in) {
                estado = S2;  // Si es 1, pasa a S2
            }
            // Si es 0, se queda en S1
            break;

        case S2:
            if (in) {
                estado = S3;  // Si es 1, pasa a S3
            } else {
                estado = S1;  // Si es 0, regresa a S1
            }
            break;

        case S3:
            if (in) {
                // Si es 1, se queda en S3
                estado = S3;
            } else {
                estado = S1;  // Si es 0, regresa a S1
            }
            break;
    }
    
    return estado;  // Retorna el estado actual después de la transición
}

int main(void) {
    char input;
    while (scanf("%hhd", &input) != EOF) {  // Lee entrada hasta EOF
        printf("Estado actual: %d\n", runFSM(input));
    }
    return 0;
}
