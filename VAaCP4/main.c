#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

int count_args(int *total_length, ...);

int main() {
    int char_count = 0;

    int arg_count = count_args(&char_count, "I'm a lonely string", NULL);

    printf("Arguments passed: %d\n", arg_count);
    printf("Characters in arguments: %d\n", char_count);

    return 0;
}

int count_args(int *total_length, ...) {
    int char_count = 0;
    int arg_count = 0;

    va_list args;
    va_start(args, total_length);

    const char * str;
    while ((str = va_arg(args, const char *)) != NULL) {
        arg_count++;
        char_count += (int)strlen(str);
    }
    va_end(args);

    *total_length = char_count;
    return arg_count;
}