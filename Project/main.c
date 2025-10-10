#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "utils/tools.h"
#include "utils/file_utils.h"

#define ROW_C 26
#define SEAT_C 7
#define INPUT_LENGTH 34
#define BUFFER_SIZE 200
#define LINE_LENGTH 100

typedef struct passenger_ {
    char first_name[32];
    char last_name[32];
    int row_num;
    char row_seat[2];
} passenger;

void initialize_rows(char rows[ROW_C][SEAT_C]);
void print_rows(char rows[ROW_C][SEAT_C]);
void update_rows(char rows[ROW_C][SEAT_C]);
int find_seat(const char *string, char c);
void reserve_a_seat(char rows[ROW_C][SEAT_C]);
void add_passenger(const char *first_name, const char *last_name, int row, char seat);
void show_passengers();
char *handle_input(int length, const char *text);
bool get_input(char *user_input, int length);
bool line_is_not_empty(char buffer[BUFFER_SIZE]);
int get_choice();
bool check_if_nums(const char *string);
char *get_name(const char* text);
int handle_row_num();
char *handle_seat();
bool check_if_seat_exists(const char * seat_str);
void passenger_to_list(passenger *passengers, int *count, const char *line);
bool check_line_commas(const char *line);
bool check_line_length(const char *string, int maxLen);
bool no_spaces(const char *string);

int main() {
    char rows[ROW_C][SEAT_C];
    bool continue_loop = true;
    initialize_rows(rows);
    update_rows(rows);

    do {
        const int choice = get_choice();
        switch (choice) {
            case 1:
                reserve_a_seat(rows);
                break;
            case 2:
                update_rows(rows);
                print_rows(rows);
                break;
            case 3:
                show_passengers();
                break;
            case 4:
                continue_loop = false;
                break;
            default:
                break;
            }

        } while (continue_loop);

    return 0;
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

void update_rows(char rows[ROW_C][SEAT_C]) {
    char line[LINE_LENGTH];
    FILE *file = open_file("seat_reservations.csv", "r");

    while (fgets(line, sizeof(line), file) != NULL) {
        if (line_is_not_empty(line)) {
            if (check_line_commas(line)) {
                char *current_line = line;
                int count = 0;

                // skip first name and last name
                while (count < 2 && (current_line = strchr(current_line, ',')) != NULL) {
                    current_line++;
                    count++;
                }

                // get the row number
                const int row_num = get_nums_from_a_string(current_line);
                if (row_num > 0) {

                    // get the seat char
                    size_t len = strlen(current_line);
                    while (len > 0 && (current_line[len - 1] == '\n' || current_line[len - 1] == '\r')) {
                        current_line[--len] = '\0';
                    }
                    const char seat_num_char = current_line[len - 1];

                    const int row_index = row_num - 1;
                    // get the seat index
                    const int seat_index = find_seat(rows[row_index], seat_num_char);
                    if (seat_index >= 0) {
                        rows[row_index][seat_index] = 'x';
                    }
                }
            }
        }
    }
    fclose(file);
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


void add_passenger(const char *first_name, const char *last_name, const int row, const char seat) {
    FILE *file = fopen("seat_reservations.csv", "a");
    if (needs_line_break()) {
        fputc('\n', file);
    }
    fprintf(file, "%s,%s,%d,%c", first_name, last_name, row, toupper(seat));
    fclose(file);
    printf("Passenger added\n");
}

/*bool needs_line_break() {
    FILE *file = open_file("seat_reservations.csv", "rb"); // open file in binary mode
    // check if the file is empty
    const bool empty_file = fseek(file, 0, SEEK_END) == 0 &&  ftell(file) == 0;
    if (!empty_file) {
        const int line_feed = '\x0A'; // represents '\n'
        // determine if a newline character is present if file is not empty
        const bool result = fseek(file, -1, SEEK_END) == 0 && fgetc(file) == line_feed;
        if (!result) {
            fclose(file);
            return true;
        }
    }
    fclose(file);
    return false;
}*/

void show_passengers() {
    struct passenger_ passengers[156];
    int count = 0;
    char buffer[BUFFER_SIZE];
    FILE *file = open_file("seat_reservations.csv", "r");

    // skip the first line
    fgets(buffer, sizeof(buffer), file);

    while (fgets(buffer, sizeof(buffer), file)) {
        if (line_is_not_empty(buffer)) {
            passenger_to_list(passengers, &count, buffer);
        }
    }
    fclose(file);


    char *titles[] = {"Firstname", "Lastname", "Row", "Seat"};
    printf("%-32s %-32s %-7s %-7s\n", titles[0], titles[1], titles[2], titles[3]);
    for (int i = 0; i < count; i++) {
        printf("%-32s %-32s %-7d %-7s\n", passengers[i].first_name, passengers[i].last_name,
            passengers[i].row_num, passengers[i].row_seat);
    }
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