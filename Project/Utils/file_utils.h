#ifndef FILE_UTILS_H
#define FILE_UTILS_H
#include <stdbool.h>

FILE *open_file(char *filename, const char *state);
bool needs_line_break();
#endif