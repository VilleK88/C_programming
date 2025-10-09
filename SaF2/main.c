#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LINE_LENGTH 82
#define MAX_LINES 100
#define FILENAME_LENGTH 34

char *get_filename();
bool get_input(char *user_input);
FILE *open_file(char *this_filename);
int count_chars(const char *characters, FILE *file);

int main() {
    //const char *characters = "aeiou";
    const char *characters = "a";

    char *filename = get_filename();
    FILE *file = open_file(filename);
    const int count = count_chars(characters, file);
    printf("Characters found: %d\n", count);

    fclose(file);
    free(filename);
    return 0;
}

char *get_filename() {
    char *user_input = malloc(FILENAME_LENGTH);
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
    if (fgets(user_input, FILENAME_LENGTH, stdin)) {
        if (strchr(user_input, '\n') == NULL) {
            int c = 0;
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Input too long (max %d characters).\n", FILENAME_LENGTH-2);
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

int count_chars(const char *characters, FILE *file) {
    int count = 0;
    char line[100];
    const int len = (int)strlen(characters);

    while (fgets(line, sizeof(line), file)) {
        for (int i = 0; line[i] != '\0'; i++) {
            for (int j = 0; j < len; j++) {
                if (characters[j] == line[i]) {
                    count++;
                }
            }
        }
    }

    return count;
}