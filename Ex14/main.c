#include <stdio.h> // printf, fgets, scanf
#include <stdlib.h> // malloc, realloc, free, atoi
#include <string.h> // strcmp, strcspn, strlen, strstr

char *handle_input();
FILE *open_file(char *this_filename);
char *read_file(FILE *this_file, int *count_out);
void print_array(char (*this_lines)[81], int this_count);

int main() {
    int count = 0;

    char *filename = handle_input();
    FILE *file = open_file(filename);
    char (*lines)[81] = read_file(file, &count);
    print_array(lines, count);

    free(lines);
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
        fprintf(stderr, "Error: could not open file: '%s'\n", this_filename);
        free(this_filename);
        exit(EXIT_FAILURE);
    }
    return file;
}

char *read_file(FILE *this_file, int *count_out) {
    int count = 0;

    char (*lines)[81] = malloc(100 * sizeof *lines);
    if (!lines) {
        printf("Memory allocation failed!\n");
        fclose(this_file);
        return NULL;
    }

    for (int i = 0; i < 100; i++) {
        if (fgets(lines[i], 81, this_file) == NULL) break;
        lines[i][strcspn(lines[i], "\n")] = '\0';
        count++;
    }

    *count_out = count;
    fclose(this_file);
    return (char*)lines;
}

void print_array(char (*this_lines)[81], int this_count) {
    for (int i = 0; i < this_count; i++) {
        printf("%s\n", this_lines[i]);
    }
}