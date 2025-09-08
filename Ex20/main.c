#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "debug.h"

int main() {
    int level = 0;
    srand((unsigned)time(NULL));

    printf("Enter a debug level (0-4): ");
    if (scanf("%d", &level) != 1 || level < 0 || level > 4) {
        fprintf(stderr, "Error: input an integer between 0 to 4:\n");
        return 1;
    }

    set_debug_level(level);

    for (int i = 0; i <= 5; i++) {
        int msg_lvl = rand() % 5;
        dprintf(msg_lvl, "Message: %d: this is an example log", i);
    }

    return 0;
}