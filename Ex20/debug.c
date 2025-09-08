#include "debug.h"
#include <stdio.h>
#include <stdarg.h>

static int g_debug_level = 0;

void set_debug_level(const int debug_level) {
    g_debug_level = debug_level;
}

int dprintf(const int debug_level, const char *fmt, ...) {
    if (debug_level < g_debug_level) {
        int written = 0;
        written += fprintf(stderr, "[DBG%d] ", debug_level);

        va_list ap;
        va_start(ap, fmt);
        written += vfprintf(stderr, fmt, ap);
        va_end(ap);

        written += fputc('\n', stderr);
        return written;
    }

    return 0;
}