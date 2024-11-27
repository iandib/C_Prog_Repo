#include <stdio.h>
#include <stdlib.h>

// Function to dynamically create a matrix
float** dinMat(int rows, int cols)
{
    // Allocate memory for an array of float pointers
    float* mat[] = (float**) calloc(rows, sizeof(float*));

    // Check if memory allocation failed
    if (mat == NULL)
    {
        return NULL;
    }

    // Allocate memory for each row and check for errors
    for (int i = 0; i < rows; i++)
    {
        // Allocate memory for each row (an array of floats)
        mat[i] = (float*) calloc(cols, sizeof(float));

        // Check if memory allocation for a row failed
        if (mat[i] == NULL)
        {
            // Free already allocated rows
            for (int j = 0; j < i; j++)
            {
                free(mat[j]);
            }

            // Free the matrix pointer array
            free(mat);

            // Return NULL to indicate an error
            return NULL;
        }
    }

    // Return the pointer to the dynamically created matrix
    return mat;
}
