#ifndef TOOLS_H
#define TOOLS_H

#include "../main.h"

void remove_newline(char *user_input);
int get_nums_from_a_string(const char *string);
void initialize_rows(char rows[ROW_C][SEAT_C]);
void print_rows(char rows[ROW_C][SEAT_C]);
#endif