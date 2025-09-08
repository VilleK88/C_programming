#include <stdio.h> // printf, fgets, scanf_s
#include <stdlib.h> // malloc, realloc, free, atoi
#include <string.h> // strcmp, strcspn, strlen, strstr, strdup, strchr
#include <stdbool.h>

typedef struct struct_line_ {
    char string[200];
    struct struct_line_ *next;
} struct_line;

char *get_filename();
FILE *open_file(char *filename);
void read_file(FILE *file, struct_line **array,  size_t *count, struct struct_line_ **head);
struct struct_line_ *append_node(struct struct_line_ *head, char *string);

int main() {
    struct_line *array = NULL;
    size_t count = 0;
    struct struct_line *head = NULL;

    char *filename = get_filename();
    FILE *file = open_file(filename);
    read_file(file, &array, &count, &head);
    //printf("Random number hexadecimal: %02x\n", 76);

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

void read_file(FILE *file, struct_line **array,  size_t *count, struct struct_line_ **head) {
    char line[200];

    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s\n", line);
        char *star = strchr(line, '*');
        struct_line **tmp = realloc(array, (*count + 1) * sizeof * array);
        array = tmp;
    }

}

struct struct_line_ *append_node(struct struct_line_ *head, char *string) {
    struct_line *newline = malloc(sizeof(*newline));
    newline->next = NULL;
    newline->string = string;
}