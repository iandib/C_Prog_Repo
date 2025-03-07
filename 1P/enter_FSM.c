#include <stdio.h>

// Función que convierte los saltos de línea a siempre usar \r\n
void convert_newlines(const char* input) 
{
    // Recorremos la cadena de entrada
    for (int array_index = 0; input[array_index] != '\0'; array_index++) 
    {
        char current_char = input[array_index];

        // Si encontramos un '\n' sin un '\r' previo
        if (current_char == '\n') 
        {
            // Antes de imprimir '\n', imprimimos '\r' para mantener el formato \r\n
            putchar('\r');
            putchar('\n');
        }
        // Si encontramos un '\r'
        else if (current_char == '\r') 
        {
            // Imprimimos '\r' y verificamos si el siguiente carácter es '\n'
            putchar('\r');

            // Si el siguiente carácter NO es '\n', agregamos uno para completar la secuencia
            if (input[array_index + 1] != '\n') 
            {
                putchar('\n');
            }
        }
        // Si no es ni '\n' ni '\r', imprimimos el carácter tal como está
        else 
        {
            putchar(current_char);
        }
    }
}

int main() 
{
    // Ejemplo de cadena de entrada con distintas combinaciones de '\r' y '\n'
    const char* input = "Hola\rMundo\nAdios\r\nFin\n\n";

    // Llamamos a la función para convertir la cadena
    convert_newlines(input);

    return 0;
}
