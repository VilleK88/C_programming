#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define filename_length 34

char *get_filename(int length);
bool get_input(char *user_input, int length);
FILE *open_file(char *filename);
void read_file(FILE *file);
int xor_get_sum(const char *dollar, const char *star);
void print_line(int sum, int result, const char *line);

int main() {

    char *filename = get_filename(filename_length);
    FILE *file = open_file(filename);
    read_file(file);

    free(filename);
    return 0;
}

char *get_filename(const int length) {
    char *string = malloc(length);
    if (string) {
        bool stop_loop = false;
        while (!stop_loop) {
            printf("Enter a filename: ");
            stop_loop = get_input(string, length);
        }
        return string;
    }
    printf("Memory allocation failed.\n");
    exit(EXIT_FAILURE);
}

bool get_input(char *user_input, const int length) {
    if(fgets(user_input, length, stdin)) {
        if (strchr(user_input, '\n') == NULL) {
            int c = 0;
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Input too long (max %d characters).\n", length-2);
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

FILE *open_file(char *filename) {
    FILE *file;
    if ((file = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Error: could not open file : '%s'\n", filename);
        free(filename);
        exit(EXIT_FAILURE);
    }
    return file;
}

void read_file(FILE *file) {
    char line[200];

    while (fgets(line, sizeof(line), file) != NULL) {
        const char *dollar = strchr(line, '$');
        if (dollar != NULL) {
            const char *star = strchr(dollar, '*');
            if (star != NULL) {
                const int sum = xor_get_sum(dollar, star);
                const int result = strtol(star + 1, NULL, 16);
                print_line(sum, result, line);
            }
        }
    }
}

int xor_get_sum(const char *dollar, const char *star) {
    int sum = 0;
    for (const char *i = dollar + 1; i < star; i++) {
        sum ^= *i;
    }
    return sum;
}

void print_line(const int sum, const int result, const char *line) {
    if (sum == result)
        printf("[ OK ]%s", line);
    else
        printf("[FAIL]%s", line);
}