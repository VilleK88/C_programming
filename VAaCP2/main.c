#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>

typedef enum { logCritical, logWarning, logInfo, logVerbose } loglevel;
static loglevel log_level;
void set_log_level(loglevel level);

int log_message(loglevel level, const char *format, ...);
const char *log_level_to_str(loglevel level);

int main() {
    set_log_level(3);
    log_message(logWarning, "Level set to %s\n", log_level_to_str(logWarning));

    return 0;
}

void set_log_level(loglevel level) {
    log_level = level;
}

int log_message(loglevel level, const char *format, ...) {
    int total = 0;
    if (level <= log_level) {
        const char *level_str = log_level_to_str(level);
        total += printf("LOG[%s]: ", level_str);
        va_list ap;
        va_start(ap, format);
        total += vprintf(format, ap);
        va_end(ap);
    }
    return total;
}

const char *log_level_to_str(loglevel level) {
    switch (level) {
        case logCritical:
            return "Critical";
        case logWarning:
            return "Warning";
        case logInfo:
            return "Info";
        case logVerbose:
            return "Verbose";
        default:
            return "Unknown";
    }
}