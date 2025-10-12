#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"
#include "utils/tools.h"
#include "utils/file_handling.h"

void initialize_rows(char rows[ROW_C][SEAT_C]);
void update_rows(char rows[ROW_C][SEAT_C]);
int get_choice();
void reserve_a_seat(char rows[ROW_C][SEAT_C]);
void print_rows(char rows[ROW_C][SEAT_C]);
void show_passengers();

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

    qsort(passengers, count, sizeof(passenger), sort_by_first_name);
    qsort(passengers, count, sizeof(passenger), sort_by_last_name);

    for (int i = 0; i < count; i++) {
        printf("%-32s %-32s %-7d %-7s\n", passengers[i].first_name, passengers[i].last_name,
            passengers[i].row_num, passengers[i].row_seat);
    }
}