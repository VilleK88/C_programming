#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h> // isdigit

void initialize_rows(char rows[26][6]);
void print_rows(char rows[26][6]);
void update_rows(char rows[26][6]);
FILE *open_file(char *filename);
int get_nums_from_a_string(const char *string);

int main() {
    char rows[26][6];
    initialize_rows(rows);
    print_rows(rows);
    update_rows(rows);
}

void initialize_rows(char rows[26][6]) {
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 6; j++) {
            const char seats[6] = {'A', 'B', 'C', 'D', 'E', 'F'};
            rows[i][j] = seats[j];
        }
    }
}

void print_rows(char rows[26][6]) {
    for (int i = 0; i < 26; i++) {
        printf("%d ", i+1);
        for (int j = 0; j < 3; j++) {
            printf("%c", rows[i][j]);
        }
        printf(" ");
        for (int j = 3; j < 6; j++) {
            printf("%c", rows[i][j]);
        }
        printf("\n");
    }
}

void update_rows(char rows[26][6]) {
    char line[100];
    FILE *file = open_file("seat_reservations.csv");

    while (fgets(line, sizeof(line), file) != NULL) {
        char *current_line = line;
        int count = 0;
        while (count < 2 && (current_line = strchr(current_line, ',')) != NULL) {
            current_line++;
            count++;
        }

        const int row_num = get_nums_from_a_string(current_line);
        printf("%d\n", row_num);
        char last;
        size_t len = strlen(current_line);
        if (len > 0 && current_line[len - 1] == '\n') {
            current_line[len- 1] = '\0';
            len--;
        }
        if (len > 0) {
            last = current_line[len - 1];
            printf("%c\n", last);
        }
        //printf("Here: %c\n", current_line[0]);
        char *row_string = malloc(count + 1);
        strcpy(row_string, current_line);
        //printf("%s\n", row_string);
        free(row_string);
    }
}

FILE *open_file(char *filename) {
    FILE *file;

    if ((file = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Error: could not open file %s\n", filename);
        free(filename);
        exit(EXIT_FAILURE);
    }

    return file;
}

int get_nums_from_a_string(const char *string) {
    char *num_char = malloc(strlen(string) + 1);

    int j = 0;
    for (int i = 0; string[i] != '\0'; i++) {
        if (isdigit(string[i])) {
            num_char[j++] = string[i];
        }
    }
    num_char[j] = '\0';
    int result = 0;
    if (j > 0)
        result = atoi(num_char);

    free(num_char);
    return result;
}