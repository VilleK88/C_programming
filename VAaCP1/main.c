#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdarg.h>

int printd(const char *format, ...);

int main() {
    int count = printd("%c %c\n", 'a', 65);
    printf("Count: %d\n", count);

    return 0;
}

int printd(const char *format, ...) {
    int total = 0;
    total += printf("DEBUG: ");
    va_list ap;
    va_start(ap, format);
    total += vprintf(format, ap);
    va_end(ap);
    return total;
}