#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *handle_input();
FILE *open_file(char *this_filename);
int *read_file(FILE *this_file, int *count_out);
void handle_print(int *numbers, int count);

int main() {
    int count = 0;

    char *filename = handle_input();
    FILE *file = open_file(filename);
    int *numbers = read_file(file, &count);
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

int *read_file(FILE *this_file, int *count_out) {
    int *numbers = NULL, temp, capacity = 0, count = 0;

    while (fscanf(this_file, "%d", &temp) == 1) {
        // Increase capacity if needed
        if (count >= capacity) {
            capacity = (capacity == 0) ? 4 : capacity * 2;
            numbers = realloc(numbers, capacity * sizeof(int));
            if (numbers == NULL) {
                printf("Memory allocation failed!\n");
                fclose(this_file);
                return 0;
            }
        }
        numbers[count++] = temp;
    }

    fclose(this_file);
    *count_out = count;

    return numbers;
}

void handle_print(int *numbers, int count) {
    int lowest = numbers[0], highest = numbers[0];

    for (int i = 0; i < count; i++) {
        if (numbers[i] < lowest) lowest = numbers[i];
        if (numbers[i] > highest) highest = numbers[i];
    }

    printf("%d numbers found.\n", count);
    printf("Lowest number: %d, highest number: %d\n", lowest, highest);
}