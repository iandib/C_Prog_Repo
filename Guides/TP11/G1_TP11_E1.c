/* *****************************************************************
    *                     FILE CONFIGURATION                      *
   ***************************************************************** */

/* --------------------------- HEADERS --------------------------- */

// Standard input-output library for printing and reading characters
#include <stdio.h>

// Standard library for memory allocation and deallocation
#include <stdlib.h>

/* -------------------------- CONSTANTS -------------------------- */

// Macro to check if a character is a valid digit
#define IS_VALID_DIGIT(c) ((c) >= '0' && (c) <= '9')

// Constant to represent an error state
#define ERROR -1


/* *****************************************************************
    *                     AUXILIARY FUNCTIONS                     *
   ***************************************************************** */

// Composes a number by appending a new digit
int compose_num(int current_num, int digit)
{
    return (current_num * 10) + digit;
}

// Reads an integer input from the user, validating character by character
int read_user_input(void)
{
    unsigned char user_char;
    int number = 0;

    // Read input until a newline character is encountered
    while ((user_char = getchar()) != '\n')
    {
        if (IS_VALID_DIGIT(user_char))
        {
            number = compose_num(number, user_char - '0');
        }

        else
        {
            // Print an error message for invalid input
            printf("Error: Input must be a positive integer.\n");
            return ERROR;
        }
    }

    return number;
}


/* *****************************************************************
    *                      MAIN FUNCTION                          *
   ***************************************************************** */

int main(void)
{
    // Prompt the user for the number of elements
    printf("Enter the number of elements: ");
    int num_elements = read_user_input();

    // Check if the number of elements is valid
    if (num_elements == ERROR || num_elements <= 0)
    {
        printf("Error: Invalid number of elements.\n");
        return ERROR;
    }

    // Allocate memory for the array
    int *array = calloc(num_elements, sizeof(int));

    if (array == NULL)
    {
        printf("Error: Memory allocation failed.\n");
        return ERROR;
    }

    // Read elements from the user and store them in the array
    for (int i = 0; i < num_elements; i++)
    {
        printf("Enter element %d: ", i + 1);
        int element = read_user_input();

        if (element == ERROR)
        {
            // Free allocated memory before exiting
            free(array);
            
            printf("Error: Invalid input for array element.\n");
            return ERROR;
        }

        array[i] = element;
    }

    // Print all elements in the array
    printf("The elements in the array are:\n");

    for (int i = 0; i < num_elements; i++)
    {
        printf("%d\n", array[i]);
    }

    // Free allocated memory
    free(array);

    // Exit the program successfully
    return 0;
}
