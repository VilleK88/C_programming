#ifndef TOOLS_H
#define TOOLS_H

#include "../main.h"

void remove_newline(char *user_input);
int get_nums_from_a_string(const char *string);
int find_seat(const char *string, char c);
char *handle_input(int length, const char *text);
bool get_input(char *user_input, int length);
bool line_is_not_empty(char buffer[BUFFER_SIZE]);
bool check_if_nums(const char *string);
char *get_name(const char* text);
int handle_row_num();
char *handle_seat();
bool check_if_seat_exists(const char * seat_str);
void passenger_to_list(passenger *passengers, int *count, const char *line);
bool check_line_commas(const char *line);
bool check_line_length(const char *string, int maxLen);
bool no_spaces(const char *string);
int sort_by_first_name(const void *a, const void *b);
int sort_by_last_name(const void *a, const void *b);
bool check_if_invalid_chars(const char *string);

#endif