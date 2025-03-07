#include <stdio.h>

// Function to check if a character is alphanumeric (letters or digits only)
int is_alphanumeric(char c)
{
    // Returns true if the character is a letter (A-Z or a-z) or a digit (0-9)
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

// Function to convert an uppercase letter to lowercase
char to_lowercase(char c)
{
    // Converts uppercase letters (A-Z) to lowercase (a-z) by adding the ASCII difference
    if (c >= 'A' && c <= 'Z')
    {
        return c + ('a' - 'A');
    }

    // Returns the character unchanged if it is already lowercase or not a letter
    return c;
}

// Function to skip non-alphanumeric characters in a string
char* skip_non_alphanumeric(char* ptr, int direction)
{
    // Loops while the character pointed to is not null and not alphanumeric
    while (*ptr && !is_alphanumeric(*ptr))
    {
        ptr += direction;
    }

    // Returns the pointer at the next valid alphanumeric character
    return ptr; 
}

// Recursive function to check if a string is a palindrome
int is_palindrome(char* left, char* right)
{
    // Skip non-alphanumeric characters at both ends
    left = skip_non_alphanumeric(left, 1);
    right = skip_non_alphanumeric(right, -1);

    // Base case: the pointers meet or cross, meaning all valid characters matched
    if (left >= right)
    {
        // The string is a palindrome
        return 1;
    }

    // Compare the characters at the current pointers, ignoring case differences
    if (to_lowercase(*left) != to_lowercase(*right))
    {
        // The string is not a palindrome
        return 0; 
    }

    // Recursive call for the next pair of characters
    return is_palindrome(left + 1, right - 1);
}

int main(void)
{
    // Input string
    char input[] = "A man, a plan, a canal, Panama";

    // Pointers to the start and end of the string
    char* start = &input[0];

    // Last valid character before the null terminator
    char* end = &input[sizeof(input) - 2]; 

    // Check if the input string is a palindrome
    if (is_palindrome(start, end))
    {
        printf("The string is a palindrome \n");
    }
    else
    {
        printf("The string is not a palindrome \n");
    }

    return 0;
}
