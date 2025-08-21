#include <stdio.h>
#include <stdlib.h>

int handle_input(int value);
int handle_memory(int *students, int size);
void initialize_students(int size, int *students);
int handle_students(int *students, int size);

int main() {
    int *students;
    int size, count;

    printf("How many students: ");
    size = handle_input(size);

    handle_memory(students, size);

    initialize_students(size, students);

    handle_students(students, size);

    free(students);

    return 0;
}

int handle_input(int value)
{
    if(scanf("%d", &value) != 1)
    {
        while(getchar() != '\n');
        printf("Invalid input\n");
    }
    return value;
}

int handle_memory(int *students, int size)
{
    students = malloc(size * sizeof(int));
    if(students == NULL)
    {
        printf("Memory allocation failed!\n");
        return 0;
    }
}

void initialize_students(int size, int *students)
{
    for(int i = 0; i < size; i++)
    {
        students[i] = -1;
    }
}

int handle_students(int *students, int size)
{
    while(1)
    {
        int num, grade;

        printf("Enter student number (1 - %d) or 0 to stop: ", size);
        num = handle_input(num);

        if(num == 0)
        {
            return 0;
        }
        else if(num < 0 || num > size)
        {
            printf("Invalid student number!\n");
        }
        else
        {
            printf("Enter grade (0 - 5) for student %d or -1 to cancel: ", num);
            grade = handle_input(grade);
            if(grade == -1)
            {
                continue;
            }
            else if(grade >= 0 && grade <= size)
            {
                students[num] = grade;
            }
            else
            {
                printf("Invalid grade!\n");
            }
        }
    }
}