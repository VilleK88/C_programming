#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "tools.h"
#include "../main.h"

void remove_newline(char *user_input) {
    if (user_input[strlen(user_input) - 1] == '\n') {
        user_input[strlen(user_input) - 1] = '\0';
    }
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
    if (j > 0) {
        result = atoi(num_char);
    }

    free(num_char);
    return result;
}

void initialize_rows(char rows[ROW_C][SEAT_C]) {
    for (int i = 0; i < ROW_C; i++) {
        for (int j = 0; j < SEAT_C; j++) {
            const char seats[SEAT_C] = {'A', 'B', 'C', 'D', 'E', 'F', '\0'};
            rows[i][j] = seats[j];
        }
    }
}

void print_rows(char rows[ROW_C][SEAT_C]) {
    for (int i = 0; i < ROW_C; i++) {

        printf("%2d ", i+1);
        for (int j = 0; j < 3; j++) {
            printf("%c", rows[i][j]);
        }

        printf("   ");
        for (int j = 3; j < SEAT_C; j++) {
            printf("%c", rows[i][j]);
        }

        printf("\n");
    }
}