#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define line_length 82
#define max_lines 100
#define filename_length 34

char *get_filename();
bool get_input(char *user_input);
FILE *open_file(char *this_filename);
char (*read_file(FILE *this_file, int *count_out))[line_length];
void convert_to_uppercase(char (*this_lines)[line_length], int this_count);
void write_to_file(char *this_filename, char (*this_lines)[line_length], int this_count);

int main() {
    int count = 0;

    char *filename = get_filename();
    FILE *file = open_file(filename);
    char (*lines)[line_length] = read_file(file, &count);
    convert_to_uppercase(lines, count);
    write_to_file(filename, lines, count);

    free(lines);
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
        fprintf(stderr, "Error: could not open file: '%s'\n", this_filename);
        exit(EXIT_FAILURE);
    }
    return file;
}

char (*read_file(FILE *this_file, int *count_out))[line_length] {
    char (*lines)[line_length] = malloc(max_lines * sizeof *lines);
    if (lines) {
        int count = 0;
        for (int i = 0; i < max_lines; i++) {
            if (fgets(lines[i], line_length, this_file) == NULL) break;
            lines[i][strcspn(lines[i], "\n")] = '\0';
            count++;
        }

        *count_out = count;
        fclose(this_file);
        return lines;
    }
    printf("Memory allocation failed!\n");
    exit(EXIT_FAILURE);
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
    if (file) {
        for (int i = 0; i < this_count; i++) {
            fprintf(file, "%s\n", this_lines[i]);
        }
        fclose(file);
    }
    else {
        fprintf(stderr, "Error: could not open file: '%s'\n", this_filename);
        fclose(file);
    }
}