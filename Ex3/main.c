#include <stdio.h>
#include <stdlib.h>

int handle_input();
void initialize_students(int **this_array, int *this_size);
int handle_memory(int **this_array, int this_size);
void handle_students(int *this_array, int this_size);
void print_students(int *this_array, int this_size);

int main() {
    int *students, size;

    initialize_students(&students, &size);
    handle_students(students, size);
    print_students(students, size);

    free(students);
    return 0;
}

int handle_input() {
    int value;

    while (1) {
        if (scanf("%d", &value) != 1) {
            while (getchar() != '\n');
            printf("Invalid input.\n");
        }
        else break;
    }

    return value;
}

void initialize_students(int **this_array, int *this_size) {
    printf("How many students: ");
    *this_size = handle_input();

    handle_memory(this_array, *this_size);

    for (int i = 0; i < *this_size; i++) {
        (*this_array)[i] = -1;
    }
}

int handle_memory(int **this_array, int this_size) {
    *this_array = malloc(this_size * sizeof(int));
    if (*this_array == NULL) {
        printf("Memory allocation failed!\n");
        return 0;
    }
    return 1;
}

void handle_students(int *this_array, int this_size) {
    printf("This size: %d\n", this_size);
    while (1) {
        printf("Enter student number (1 - %d) or 0 to stop: ", this_size);
        int num = handle_input();
        if (num == 0)
            break;
        else if (num < 1 || num > this_size) {
            printf("Invalid student number!\n");
        }
        else {
            printf("Enter grade (0 - 5) for student %d or -1 to cancel: ", num);
            int const grade = handle_input();
            if (grade == -1)
                continue;
            else {
                if (grade < 0 || grade > 5)
                    printf("Invalid grade!\n");
                else
                    this_array[num-1] = grade;
            }
        }
    }
}

void print_students(int *this_array, int this_size) {
    printf("Student   Grade\n");
    for (int i = 0; i < this_size; i++) {
        if (this_array[i] == -1)
            printf("%d %11s\n", i + 1, "N/A");
        else
            printf("%d %9d\n", i + 1, this_array[i]);
    }
}