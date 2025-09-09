#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void initialize_rows(char rows[26][6]);
void print_rows(char rows[26][6]);
void load_rows(char rows[26][6]);
FILE *open_file(char *filename);

int main() {
    char rows[26][6];
    initialize_rows(rows);
    print_rows(rows);
    load_rows(rows);
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

void load_rows(char rows[26][6]) {
    char line[100];
    FILE *file = open_file("seat_reservations.csv");

    while (fgets(line, sizeof(line), file) != NULL) {
        //char *comma = strchr(line + count, ',');
        char *current_line = line;
        int count = 0;
        while (count < 2 && (current_line = strchr(current_line, ',')) != NULL) {
            current_line++;
            count++;
        }
        char *row;
        for (int i = 0; i < strlen(current_line); i++) {
            if (current_line[i] != ',') {
                row = realloc(row, sizeof(current_line[i]));
                if (!row) {
                    free(row);
                }
                row += current_line[i];
            }

        }
        printf("%s\n", row);
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