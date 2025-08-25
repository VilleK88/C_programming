#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *handle_input();
void handle_program();

int main() {
    handle_program();

    return 0;
}

char *handle_input() {
    char *string = malloc(32);
    if (!string) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    if (!fgets(string, 32, stdin)) { // EOF
        free(string);
        return NULL;
    }

    string[strcspn(string, "\n")] = '\0';

    return string;
}

void handle_program() {
    while (1) {
        printf("Enter a string: ");
        char *string = handle_input();
        int length = strlen(string);

        if (strcmp(string, "stop") == 0) {
            free(string);
            break;
        }
        else
            printf("Length of the string: %zu.\n", length);

        free(string);
    }
}