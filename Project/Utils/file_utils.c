#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

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