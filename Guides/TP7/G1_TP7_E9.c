#include <stdio.h>

// Enum to represent the states of the FSM
typedef enum 
{
    NORMAL,                 // Normal reading state (S0)
    POSSIBLE_COMMENT,       // Possible start of a comment (S1)
    SINGLE_LINE_COMMENT,    // Inside a single-line comment (S2)
    MULTI_LINE_COMMENT,     // Inside a multi-line comment (S3)
    POSSIBLE_END_COMMENT    // Possible end of a multi-line comment (S4)
} State;

// Function to remove comments from an input file
void remove_comments(FILE* input, FILE* output)
{
    // Initialize the FSM state to NORMAL
    State state = NORMAL; 

    // Variables to store current and next character
    int current_char, next_char;

    // Read the first character from the input file
    current_char = fgetc(input);

    // Loop through the input file until the end of the file (EOF)
    while (current_char != EOF)
    {
        // State machine to handle transitions and processing
        switch (state)
        {
            case NORMAL:

                // Check if the current character is a potential start of a comment
                if (current_char == '/')
                {
                    state = POSSIBLE_COMMENT;
                }

                else
                {
                    // Write non-comment characters to the output file
                    fputc(current_char, output);
                }

                break;

            case POSSIBLE_COMMENT:

                // Read the next character to determine the type of comment or not
                next_char = fgetc(input);

                if (next_char == '/')
                {
                    // Transition to SINGLE_LINE_COMMENT if "//" is detected
                    state = SINGLE_LINE_COMMENT; 
                }

                else if (next_char == '*')
                {
                    // Transition to MULTI_LINE_COMMENT if "/*" is detected
                    state = MULTI_LINE_COMMENT;
                }

                else
                {
                    // If not a comment, output the '/' and next character
                    fputc('/', output);
                    fputc(next_char, output);
                    state = NORMAL;
                }

                break;

            case SINGLE_LINE_COMMENT:

                // Ignore all characters until a newline is detected
                if (current_char == '\n')
                {
                    // Write the newline character to maintain formatting
                    fputc(current_char, output); 

                    // Return to NORMAL state after ending the comment
                    state = NORMAL;
                }

                break;

            case MULTI_LINE_COMMENT:

                // Check if the current character might indicate the end of the comment
                if (current_char == '*')
                {
                    state = POSSIBLE_END_COMMENT;
                }

                break;

            case POSSIBLE_END_COMMENT:

                // Confirm the end of a multi-line comment with a '/'
                if (current_char == '/')
                {
                    state = NORMAL;
                }

                else if (current_char == '*')
                {
                    // Stay in POSSIBLE_END_COMMENT if '*' is repeated
                    state = POSSIBLE_END_COMMENT;
                }

                else
                {
                    // Return to MULTI_LINE_COMMENT if no '/' is found
                    state = MULTI_LINE_COMMENT;
                }

                break;
        }

        // Read the next character to continue processing
        current_char = fgetc(input);
    }
}


int main(void)
{
    // Open the input file for reading
    FILE* input = fopen("input.c", "r");

    // Open the output file for writing
    FILE* output = fopen("output.c", "w");

    // Check if the files were opened successfully
    if (input == NULL || output == NULL)
    {
        printf("Error: Unable to open files.\n");
        return 1;
    }

    // Call the function to remove comments from the input file
    remove_comments(input, output);

    // Close both the input and output files
    fclose(input);
    fclose(output);

    // Inform the user that the process was successful
    printf("Comments successfully removed. Check 'output.c'.\n");

    return 0;
}
