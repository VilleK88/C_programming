#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tools.h"
#include "../main.h"
#include "file_handling.h"

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

int find_seat(const char *string, const char c) {
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == c) {
            return i;
        }
    }
    return -1;
}

void reserve_a_seat(char rows[ROW_C][SEAT_C]) {
    bool continue_loop = true;

    do {
        char *first_name = get_name("Enter first name: ");
        char *last_name = get_name("Enter last name: ");

        print_rows(rows);

        const int row_num = handle_row_num();
        char *seat_str = handle_seat();

        // converts seat letter to array index
        const int seat_int = *seat_str - 'A';
        if (rows[row_num-1][seat_int] != 'x') {
            add_passenger(first_name, last_name, row_num, *seat_str);
            continue_loop = false;
        }
        else {
            printf("Seat already taken.\n");
        }

        free(first_name);
        free(last_name);
        free(seat_str);
    } while (continue_loop);
}

char *handle_input(const int length, const char *text) {
    char *string = malloc(length);
    if (string) {
        bool stop_loop = false;
        while (!stop_loop) {
            printf("%s", text);
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
        remove_newline(user_input);
        if (user_input[0] == '\0') {
            printf("Empty input.\n");
            return false;
        }

        return true;
    }

    return false;
}

bool line_is_not_empty(char buffer[BUFFER_SIZE]) {
    if (strcmp(buffer, "\n") != 0 &&
            strcmp(buffer, "\r\n") != 0 &&
            strcmp(buffer, "\0") != 0) {
        return true;
    }

    return false;
}

int get_choice() {
    long int value = 0;
    bool continue_loop = true;

    do {
        printf("1) reserve a seat\n2) seat map\n3) show passengers\n4) exit\n");
        char *choice = handle_input(34, "Enter choice: ");
        char *endPtr;
        const long int val = strtol(choice, &endPtr, 10);
        if (*endPtr == '\0' && val >= 1 && val <= 4) {
            value = val;
            continue_loop = false;
        }
        else {
            if (*endPtr != '\0')
                printf("Invalid input (only numbers allowed): %s\n", choice);
            else
                printf("Input out of range: %d\n", (int)val);
        }

        free(choice);
    } while (continue_loop);

    return value;
}

bool check_if_nums(const char *string) {
    const int len = (int)strlen(string);
    for (int i = 0; i < len; i++) {
        if (isdigit(string[i])) {
            return true;
        }
    }

    return false;
}

char *get_name(const char *text) {
    char *name = NULL;
    bool continue_loop = true;

    do {
        name = handle_input(INPUT_LENGTH, text);
        if (check_if_nums(name))
            printf("Invalid input (only letters allowed): %s\n", name);
        else
            continue_loop = false;
    } while (continue_loop);

    return name;
}

int handle_row_num() {
    int row_num = 0;
    bool continue_loop = true;

    do {
        char *row_str = handle_input(INPUT_LENGTH, "Enter a row number: ");
        char *endPtr;
        const long int val = strtol(row_str, &endPtr, 10);
        if (*endPtr == '\0' && val >= 1 && val <= ROW_C) {
            row_num = val;
            continue_loop = false;
        }
        else {
            if (*endPtr != '\0') {
                printf("Invalid input (only numbers allowed): %s\n", row_str);
            }
            else {
                printf("Input out of range: %d\n", (int)val);
                printf("Choose seat row between 1 - %d\n", ROW_C);
            }
        }

        free(row_str);
    } while (continue_loop);

    return row_num;
}

char *handle_seat() {
    char *seat_str;
    bool continue_loop = true;

    do {
        seat_str = handle_input(INPUT_LENGTH, "Enter a seat (A-F): ");
        if (!check_if_nums(seat_str)) {
            *seat_str = (char)toupper(*seat_str);
            if (check_if_seat_exists(seat_str)) {
                continue_loop = false;
            }
            else {
                printf("Invalid input. No seat: %s\n", seat_str);
                free(seat_str);
            }
        }
        else {
            printf("Invalid input(only letters allowed): %s\n", seat_str);
            free(seat_str);
        }

    } while (continue_loop);

    return seat_str;
}

bool check_if_seat_exists(const char *seat_str) {
    const char seats[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    const int len = (int)strlen(seats);

    for (int i = 0; i < len; i++) {
        if (seats[i] == seat_str[0]) {
            return true;
        }
    }

    return false;
}

void passenger_to_list(passenger *passengers, int *count, const char *line) {
    if (check_line_commas(line)) {
        char *first_comma = strchr(line, ',');
        *first_comma = '\0';

        if (check_line_length(line, INPUT_LENGTH - 2) && !check_if_nums(line)
            & no_spaces(line)) {
            strncpy(passengers[*count].first_name, line,sizeof passengers[*count].first_name - 1);
            passengers[*count].first_name[sizeof passengers[*count].first_name - 1] = '\0';


            first_comma++;
            char *second_comma = strchr(first_comma, ',');
            *second_comma = '\0';
            if (check_line_length(first_comma, INPUT_LENGTH - 2) && !check_if_nums(second_comma)
                && no_spaces(first_comma)) {
                strncpy(passengers[*count].last_name, first_comma,sizeof passengers[*count].last_name - 1);
                passengers[*count].last_name[sizeof passengers[*count].last_name - 1] = '\0';

                second_comma++;
                char *third_comma = strchr(second_comma, ',');
                *third_comma = '\0';
                if (check_line_length(second_comma, 5) && check_if_nums(second_comma)
                    && no_spaces(second_comma)) {
                    passengers[*count].row_num = (int)strtol(second_comma, NULL, 10);

                    char *line_after_last_comma = third_comma + 1;
                    line_after_last_comma[strcspn(line_after_last_comma, "\r\n")] = '\0';
                    if (check_line_length(line_after_last_comma, 5) && !check_if_nums(line_after_last_comma)
                        && no_spaces(line_after_last_comma)) {
                        passengers[*count].row_seat[0] = line_after_last_comma[0];
                        passengers[*count].row_seat[1] = '\0';

                        (*count)++;
                    }
                }
            }
        }
    }
}

bool check_line_commas(const char *line) {
    const int len = (int)strlen(line);
    int comma_count = 0;

    for (int i = 0; i < len; i++) {
        if (line[i] == ',')
            comma_count++;
    }

    if (comma_count != 3)
        return false;

    return true;
}

bool check_line_length(const char *string, const int maxLen) {
    const int len = (int)strlen(string);
    if (len > 0 && len <= maxLen)
        return true;

    return false;
}

bool no_spaces(const char *string) {
    const int len = (int)strlen(string);
    for (int i = 0; i < len; i++) {
        if (string[i] == ' ')
            return false;
    }

    return true;
}