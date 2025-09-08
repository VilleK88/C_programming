#include <stdio.h> // printf, fgets, scanf_s
#include <stdlib.h> // malloc, realloc, free, atoi
#include <string.h> // strcmp, strcspn, strlen, strstr, strdup, strchar
#include <stdbool.h>

void initialize_rows(char rows[26][6]);
void print_rows(char rows[26][6]);

int main() {
    char rows[26][6];
    initialize_rows(rows);
    print_rows(rows);
}

void initialize_rows(char rows[26][6]) {
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 6; j++) {
            const char seats[6] = {'A', 'B', 'C', 'D', 'E', 'F'};
            rows[i][j] = seats[j];
            //printf("%c\n", seats[j]);
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