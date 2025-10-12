#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include <stdio.h>
#include <stdbool.h>

FILE *open_file(char *filename, const char *state);
bool needs_line_break();
void add_passenger(const char *first_name, const char *last_name, int row, char seat);

#endif