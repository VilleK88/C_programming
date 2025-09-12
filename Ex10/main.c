#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *handle_input();
char *input_warning_and_free_memory(char *description, char* string);

int main() {
    char *string = NULL;
    bool check = true;

    do {
        printf("Enter a string: ");
        string = handle_input();
        if (string != NULL) {
            const size_t length = strlen(string);
            printf("Length of the string: %zu.\n", length);
            if(strcmp(string, "stop") == 0)
                check = false;
        }
        free(string);
    } while (check);

    return 0;
}

char *handle_input() {
    const int length = 33;
    char *string = malloc(length);

    if (string) {
        if (fgets(string, length, stdin)) {
            if (strchr(string, '\n') == NULL) {
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF){}
                return input_warning_and_free_memory("Input too long (max 32 characters).", string);
            }
            // replaces the first '\n' in the string with '\0' to remove the newline
            string[strcspn(string, "\n")] = '\0';

            if (string[0] == '\0')
                return input_warning_and_free_memory("Empty input.", string);
        }
    }
    else
        return input_warning_and_free_memory("Memory allocation failed.", string);

    return string;
}

char *input_warning_and_free_memory(char *description, char* string) {
    printf("%s\n", description);
    free(string);
    return NULL;
}