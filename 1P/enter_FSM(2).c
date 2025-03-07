#include <stdio.h>

// Función que convierte saltos de línea a \r\n usando una FSM con switch
void convert_newlines_fsm(const char* input) 
{
    enum State { NORMAL, SEEN_CR, SEEN_LF };
    enum State current_state = NORMAL;

    for (int array_index = 0; input[array_index] != '\0'; array_index++) 
    {
        char current_char = input[array_index];

        switch (current_state) 
        {
            case NORMAL:
                if (current_char == '\n') 
                {
                    putchar('\r');
                    putchar('\n');
                    current_state = SEEN_LF; // Transición
                } 
                else if (current_char == '\r') 
                {
                    putchar('\r');
                    current_state = SEEN_CR; // Transición
                } 
                else 
                {
                    putchar(current_char);
                }
                break;

            case SEEN_CR:
                if (current_char == '\n') 
                {
                    putchar('\n');
                } 
                else 
                {
                    putchar('\n'); // Forzar un \n después del \r
                    putchar(current_char);
                }
                current_state = NORMAL; // Transición de vuelta
                break;

            case SEEN_LF:
                // Aquí no necesitamos hacer nada especial
                current_state = NORMAL; // Vuelve al estado normal
                break;
        }
    }
}

int main() 
{
    const char* input = "Hola\rMundo\nAdios\r\nFin\n\n";
    convert_newlines_fsm(input);
    return 0;
}
