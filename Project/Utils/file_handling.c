#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#include "../main.h"
#include "tools.h"

FILE *open_file(char *filename, const char *state) {
    FILE *file;
    if ((file = fopen(filename, state)) == NULL) {
        fprintf(stderr, "Error: could not open file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    return file;
}

bool needs_line_break() {
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