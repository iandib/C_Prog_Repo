#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Maximum length for name and surname
#define MAX 50

// Maximum number of students in the class 
#define CLASS 30

// Define the student structure
typedef struct
{
    char name[MAX];
    char surname[MAX];
    float mark;
} students_t;


// Comparison function for qsort
int compare(const void* p1, const void* p2)
{
    // Cast to students_t
    const students_t* studentA = (const students_t*) p1; 
    const students_t* studentB = (const students_t*) p2;

    // Compare by marks in descending order
    if (studentA->mark < studentB->mark)
    {
        // studentB comes before studentA
        return 1; 
    }
    
    else if (studentA->mark > studentB->mark)
    {
        // studentA comes before studentB
        return -1;
    }

    // If marks are equal, compare by surname in ascending order
    int surname_cmp = strcmp(studentA->surname, studentB->surname);
    if (surname_cmp != 0)
    {
        // Return result of surname comparison
        return surname_cmp;
    }

    // If surname is also the same, compare by name in ascending order
    return strcmp(studentA->name, studentB->name);
}


int main(void)
{
    // Initialize an array of students
    students_t students[CLASS] =
    {
        {"Adams", "Douglas", 7.8},
        {"Aladin", "Nikko", 7.8},
        {"Bob", "Nikko", 8.5},
        {"Charlie", "Douglas", 7.8},
        {"Eve", "Smith", 9.2}
    };

    // Number of students in the array
    size_t num_students = 5;

    // Sort the students array using qsort
    qsort(students, num_students, sizeof(students_t), compare);

    // Print the sorted array
    printf("Sorted students:\n");
    for (size_t i = 0; i < num_students; i++)
    {
        printf("Name: %s, Surname: %s, Mark: %.2f\n", students[i].name, students[i].surname, students[i].mark);
    }

    return 0;
}
