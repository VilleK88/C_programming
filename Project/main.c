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
int find_seat(const char *string, char c);

int main() {
    char rows[26][6];
    initialize_rows(rows);
    print_rows(rows);
    update_rows(rows);
    printf("\n");
    print_rows(rows);
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
        size_t len = strlen(current_line);
        if (len > 0 && current_line[len - 1] == '\n') {
            current_line[len- 1] = '\0';
            len--;
        }
        if (len > 0) {
            const char last = current_line[len - 1];
            if (row_num > 0) {
                const int seat_num = find_seat(rows[row_num], last);
                rows[row_num][seat_num] = 'x';
            }
        }
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

int find_seat(const char *string, const char c) {
    if (string != NULL) {
        for (int i = 0; string[i] != '\n'; i++) {
            if (string[i] == c)
                return i;
        }
    }
    return 0;
}