#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_filename();
FILE *open_file(char *filename);
void read_file(FILE *file);
int xor_get_sum(const char *dollar, const char *star);
void print_line(int sum, int result, const char *line);

int main() {

    char *filename = get_filename();
    FILE *file = open_file(filename);
    read_file(file);

    free(filename);
    return 0;
}

char *get_filename() {
    char *string = malloc(32);
    if (!string) {
        printf("Memory allocation failed.\n");
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