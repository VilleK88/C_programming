#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *handle_input();

int main() {
    char *string = NULL;

    do {
        printf("Enter a string: ");
        string = handle_input();
        const size_t length = strlen(string);
        printf("Length of the string: %zu.\n", length);
    } while (strcmp(string, "stop") != 0);

    free(string);

    return 0;
}

char *handle_input() {
    char *string = malloc(32);
    if (!string) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    if (!fgets(string, 32, stdin)) {
        free(string);
        return NULL;
    }

    string[strcspn(string, "\n")] = '\0';

    return string;
}