#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    // Flag to track if the next argument is a value for a key
    bool key_flag = false;

    // Arrays to store keys, values, and parameters
    char* keys[argc - 1];
    char* values[argc - 1];
    char* parameters[argc - 1];

    // Counters for the total number of keys, values, and parameters
    int total_keys = 0;
    int total_values = 0;
    int total_parameters = 0;


    // Iterate through the command-line arguments, starting from index 1
    for (int i = 1; i < argc; i++)
    {
        // Check if the argument starts with a dash, indicating a key
        if (*argv[i] == '-')
        {
            // Store the key and increment the key counter
            keys[total_keys] = argv[i];
            total_keys++;

            // Set the flag indicating the next argument is a value
            key_flag = true;
        }

        // If the flag is set, the current argument is a value for the last key
        else if (key_flag == true)
        {
            // Store the value and increment the value counter
            values[total_values] = argv[i];
            total_values++;

            // Reset the flag as the value has been processed
            key_flag = false;
        }

        // If the argument is neither a key nor a value, it is a parameter
        else
        {
            // Store the parameter and increment the parameter counter
            parameters[total_parameters] = argv[i];
            total_parameters++;
        }
    }

    // Check if the last key is missing a value
    if (key_flag)
    {
        // Print an error message and exit the program
        fprintf(stderr, "Error: Key %s is missing a value.\n", keys[total_keys - 1]);
        exit(EXIT_FAILURE);
    }


    // Print all keys and their corresponding indices
    for (int i = 0; i < total_keys; i++)
    {
        printf("Key %d: %s\n", i + 1, keys[i]);
    }

    // Print all values and their corresponding indices
    for (int i = 0; i < total_values; i++)
    {
        printf("Value %d: %s\n", i + 1, values[i]);
    }

    // Print all parameters and their corresponding indices
    for (int i = 0; i < total_parameters; i++)
    {
        printf("Parameter %d: %s\n", i + 1, parameters[i]);
    }

    return 0;
}
