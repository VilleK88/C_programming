#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define filename_length 34

char *get_filename();
bool get_input(char *user_input);
FILE *open_file(char *this_filename);
int *read_file(FILE *this_file, int *count);
void handle_print(const int *numbers, int count);

int main() {
    int count = 0;

    char *filename = get_filename();
    FILE *file = open_file(filename);
    int *numbers = read_file(file, &count);
    if (numbers != NULL)
        handle_print(numbers, count);

    free(numbers);
    free(filename);
    return 0;
}

char *get_filename() {
    char *user_input = malloc(filename_length);
    if (user_input) {
        bool stop_loop = false;
        while (!stop_loop) {
            printf("Enter a filename: ");
            stop_loop = get_input(user_input);
        }
        return user_input;
    }
    printf("Memory allocation failed.\n");
    exit(EXIT_FAILURE);
}

bool get_input(char *user_input) {
    if (fgets(user_input, filename_length, stdin)) {
        if (strchr(user_input, '\n') == NULL) {
            int c = 0;
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Input too long (max %d characters).\n", filename_length-2);
            return false;
        }
        user_input[strcspn(user_input, "\n")] = '\0';
        if (user_input[0] == '\0') {
            printf("Empty input.\n");
            return false;
        }
        return true;
    }
    return false;
}

FILE *open_file(char *this_filename) {
    FILE *file;
    if ((file = fopen(this_filename, "r")) == NULL) {
        fprintf(stderr, "Error: could not open file '%s'\n", this_filename);
        exit(EXIT_FAILURE);
    }
    return file;
}

int *read_file(FILE *this_file, int *count) {
    int *numbers = NULL;
    int temp;

    while (fscanf(this_file, "%d", &temp) == 1) {
        int *buffer = realloc(numbers, sizeof(temp) * (*count+1));
        if (!buffer) {
            free(buffer);
        }
        else {
            numbers = buffer;
            numbers[(*count)++] = temp;
        }
    }

    fclose(this_file);
    return numbers;
}

void handle_print(const int *numbers, const int count) {
    int lowest = numbers[0];
    int highest = numbers[0];

    for (int i = 0; i < count; i++) {
        if (numbers[i] < lowest)
            lowest = numbers[i];
        if (numbers[i] > highest)
            highest = numbers[i];
    }

    printf("%d numbers found.\n", count);
    printf("Lowest number: %d, highest number: %d\n", lowest, highest);
}