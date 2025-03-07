#include <stdio.h>
#include <string.h>

// Maximum length for name and surname
#define MAX 50

// Define the student structure
typedef struct
{
    char name[MAX];
    char surname[MAX];
    float mark;
} student_t;


// Swap two student_t elements
void swap(student_t* studentA, student_t* studentB)
{
    // Temporary structure to hold the value of studentA
    student_t temp = *studentA;
    *studentA = *studentB;
    *studentB = temp;
}


// Comparison function to decide the order of two students
int compare_students(const student_t* studentA, const student_t* studentB)
{
    // Compare by marks in descending order
    if (studentA->mark > studentB->mark)
    {
        return -1;
    }

    else if (studentA->mark < studentB->mark)
    {
        return 1;
    }

    // If marks are equal, compare by surname in ascending order
    int surname_cmp = strcmp(studentA->surname, studentB->surname);
    if (surname_cmp != 0)
    {
        return surname_cmp;
    }

    // If surname is also the same, compare by name in ascending order
    return strcmp(studentA->name, studentB->name);
}


// Bubble sort implementation for student_t array
void bubble_sort(student_t array[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            // Use the comparison function to decide order
            if (compare_students(&array[j], &array[j + 1]) > 0)
            {
                swap(&array[j], &array[j + 1]);
            }
        }
    }
}


// Main function to test the implementation
int main()
{
    // Example student array
    student_t students[] =
    {
        {"Alice", "Brown", 8.5},
        {"Bob", "Smith", 9.0},
        {"Charlie", "Brown", 8.5},
        {"Diana", "Smith", 9.0},
        {"Eve", "Johnson", 7.0}
    };

    // Size of the array
    int size = sizeof(students) / sizeof(students[0]);

    // Sort the array
    bubble_sort(students, size);

    // Print the sorted array
    printf("Sorted students:\n");
    for (int i = 0; i < size; i++)
    {
        printf("%s %s: %.2f\n", students[i].name, students[i].surname, students[i].mark);
    }

    return 0;
}
