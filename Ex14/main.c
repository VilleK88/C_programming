#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *handle_input();
FILE *open_file(char *this_filename);
char *read_file(FILE *this_file, int *count_out);
void convert_to_uppercase(char (*this_lines)[81], int this_count);
void write_to_file(char *this_filename, char (*this_lines)[81], int this_count);

int main() {
    int count = 0;

    char *filename = handle_input();
    FILE *file = open_file(filename);
    char (*lines)[81] = read_file(file, &count);
    convert_to_uppercase(lines, count);
    write_to_file(filename, lines, count);

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

void convert_to_uppercase(char (*this_lines)[81], int this_count) {
    for (int i = 0; i < this_count; i++) {
        for (int j = 0; j < strlen(this_lines[i]); j++) {
            char c = this_lines[i][j];
            this_lines[i][j] = toupper(c);
        }
    }
}


void write_to_file(char *this_filename, char (*this_lines)[81], int this_count) {
    FILE *file = fopen(this_filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: could not open file: '%s'\n", this_filename);
        free(this_filename);
        return;
    }

    for (int i = 0; i < this_count; i++) {
        fprintf(file, "%s\n", this_lines[i]);
    }

    fclose(file);
}