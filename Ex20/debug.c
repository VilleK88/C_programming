#include "debug.h"
#include <stdio.h>
#include <stdarg.h>

static int d_debug_level = 0;

void set_debug_level(const int debug_level) {
    d_debug_level = debug_level;
}

int dprintf(const int debug_level, const char *fmt, ...) {
    if (debug_level <= d_debug_level) {
        int bytes_written = 0;
        bytes_written += fprintf(stderr, "[DBG%d] ", debug_level);

        va_list ap;
        va_start(ap, fmt);
        bytes_written += vfprintf(stderr, fmt, ap);
        va_end(ap);

        bytes_written += fputc('\n', stderr);
        return bytes_written;
    }

    return 0;
}