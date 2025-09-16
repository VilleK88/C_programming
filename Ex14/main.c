#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define line_length 82
#define max_lines 100
#define filename_length 32

char *get_filename();
FILE *open_file(char *this_filename);
char (*read_file(FILE *this_file, int *count_out))[line_length];
void convert_to_uppercase(char (*this_lines)[line_length], int this_count);
void write_to_file(char *this_filename, char (*this_lines)[line_length], int this_count);

int main() {
    int count = 0;

    char *filename = get_filename();
    FILE *file = open_file(filename);
    char (*lines)[line_length] = read_file(file, &count);
    if (lines != NULL) {
        convert_to_uppercase(lines, count);
        write_to_file(filename, lines, count);
        free(lines);
    }

    return 0;
}

char *get_filename() {
    char *string = malloc(filename_length);
    if (!string) {
        printf("Memory allocation failed!\n");
        free(string);
        return NULL;
    }

    printf("Enter a filename: ");
    if (!fgets(string, filename_length, stdin)) {
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

char (*read_file(FILE *this_file, int *count_out))[line_length] {
    int count = 0;
    char (*lines)[line_length] = malloc(100 * sizeof *lines);
    if (!lines) {
        printf("Memory allocation failed!\n");
        fclose(this_file);
        return NULL;
    }

    for (int i = 0; i < max_lines; i++) {
        if (fgets(lines[i], line_length, this_file) == NULL) break;
        lines[i][strcspn(lines[i], "\n")] = '\0';
        count++;
    }

    *count_out = count;
    fclose(this_file);
    return lines;
}

void convert_to_uppercase(char (*this_lines)[line_length], const int this_count) {
    for (int i = 0; i < this_count; i++) {
        for (int j = 0; j < strlen(this_lines[i]); j++) {
            const char c = this_lines[i][j];
            this_lines[i][j] = toupper(c);
        }
    }
}

void write_to_file(char *this_filename, char (*this_lines)[line_length], const int this_count) {
    FILE *file = fopen(this_filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: could not open file: '%s'\n", this_filename);
        free(this_filename);
        fclose(file);
        return;
    }

    for (int i = 0; i < this_count; i++) {
        fprintf(file, "%s\n", this_lines[i]);
    }

    fclose(file);
}