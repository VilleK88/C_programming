#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "debug.h"
#include <stdbool.h>
#include <string.h>

#define INPUT_LENGTH 34

char *handle_input(int length);
bool get_input(char *user_input, int length);
void remove_newline(char *user_input);

int main() {
    int level = 0;
    bool continue_loop = true;
    srand((unsigned)time(NULL));

    do {
        char *level_str = handle_input(INPUT_LENGTH);
        char *endPtr;
        const long int level_int = strtol(level_str, &endPtr, 10);
        if (*endPtr == '\0' && level_int >= 0 && level_int <= 4) {
            level = level_int;
            continue_loop = false;
        }
        else {
            if (*endPtr == '\0')
                printf("Input out of range %d\n", (int)level_int);
            else
                printf("Invalid input: %s\n", level_str);
        }
        free(level_str);
    } while (continue_loop);

    set_debug_level(level);

    for (int i = 0; i <= 5; i++) {
        const int msg_lvl = rand() % 5;
        dprintf(msg_lvl, "Message: %d: this is an example log", i+1);
    }

    return 0;
}

char *handle_input(const int length) {
    char *string = malloc(length);
    if (string) {
        bool stop_loop = false;
        while (!stop_loop) {
            printf("Enter a debug level (0-4): ");
            stop_loop = get_input(string, length);
        }
        return string;
    }
    printf("Memory allocation failed.\n");
    exit(EXIT_FAILURE);
}

bool get_input(char *user_input, const int length) {
    if(fgets(user_input, length, stdin)) {
        if (strchr(user_input, '\n') == NULL) {
            int c = 0;
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Input too long (max %d characters).\n", length-2);
            return false;
        }
        remove_newline(user_input);
        if (user_input[0] == '\0') {
            printf("Empty input.\n");
            return false;
        }
        return true;
    }
    return false;
}

void remove_newline(char *user_input) {
    if (user_input[strlen(user_input) - 1] == '\n') {
        user_input[strlen(user_input) - 1] = '\0';
    }
}