#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H
#include <stdbool.h>
#include "../main.h"

FILE *open_file(char *filename, const char *state);
bool needs_line_break();
void update_rows(char rows[ROW_C][SEAT_C]);
void add_passenger(const char *first_name, const char *last_name, int row, char seat);
void show_passengers();

#endif