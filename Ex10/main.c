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
    } while (check == true);

    free(string);
    return 0;
}

char *handle_input() {
    char *string = malloc(32);
    if (!string)
        return input_warning_and_free_memory("Memory allocation failed.\n", string);

    if (!fgets(string, 32, stdin))
        return input_warning_and_free_memory("The input reading failed (EOF or input error).\n", string);

    string[strcspn(string, "\n")] = '\0';

    if (string[0] == '\0')
        return input_warning_and_free_memory("Empty input.\n", string);

    return string;
}

char *input_warning_and_free_memory(char *description, char* string) {
    printf("%s", description);
    free(string);
    return NULL;
}