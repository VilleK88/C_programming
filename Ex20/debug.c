#include "debug.h"
#include <stdio.h>
#include <stdarg.h>

static int d_debug_level = 0;

void set_debug_level(const int debug_level) {
    d_debug_level = debug_level;
}

int dprintf(const int debug_level, const char *fmt, ...) {
    if (debug_level <= d_debug_level) {
        int standard_error = 0;
        standard_error += fprintf(stderr, "[DBG%d] ", debug_level);

        va_list ap;
        va_start(ap, fmt);
        standard_error += vfprintf(stderr, fmt, ap);
        va_end(ap);

        standard_error += fputc('\n', stderr);
        return standard_error;
    }

    return 0;
}