#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *handle_input();
FILE *open_file(char *this_filename);
int *read_file(FILE *this_file, int *this_count);
void handle_print(const int *this_numbers, int this_count);

int main() {
    int count = 0;

    char *filename = handle_input();
    FILE *file = open_file(filename);
    int *numbers = read_file(file, &count);
    if (numbers != NULL)
        handle_print(numbers, count);

    free(numbers);
    free(filename);

    return 0;
}

char *handle_input() {
    char *string = malloc(32);
    if (!string) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    printf("Enter a filename: ");
    if (!fgets(string, 32, stdin)) {
        free(string);
        return NULL;
    }

    string[strcspn(string, "\n")] = '\0';

    return string;
}

FILE *open_file(char *this_filename) {
    FILE *file;

    if ((file = fopen(this_filename, "r")) == NULL) {
        fprintf(stderr, "Error: could not open file '%s'\n", this_filename);
        free(this_filename);
        exit(EXIT_FAILURE);
    }

    return file;
}

int *read_file(FILE *this_file, int *this_count) {
    int *numbers = NULL, temp;

    while (fscanf(this_file, "%d", &temp) == 1) {
        int *buffer = realloc(numbers, sizeof(temp) * (*this_count+1));
        if (!buffer) {
            free(buffer);
        }
        else {
            numbers = buffer;
            numbers[(*this_count)++] = temp;
        }
    }

    fclose(this_file);
    return numbers;
}

void handle_print(const int *this_numbers, const int this_count) {
    int lowest = this_numbers[0], highest = this_numbers[0];

    for (int i = 0; i < this_count; i++) {
        if (this_numbers[i] < lowest)
            lowest = this_numbers[i];
        if (this_numbers[i] > highest)
            highest = this_numbers[i];
    }

    printf("%d numbers found.\n", this_count);
    printf("Lowest number: %d, highest number: %d\n", lowest, highest);
}