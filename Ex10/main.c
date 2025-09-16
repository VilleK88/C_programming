#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define input_length 34

char *handle_input(int length);
bool get_input(char *user_input, int length);

int main() {
    char *string = NULL;
    bool check = true;

    do {
        string = handle_input(input_length);
        if (string != NULL) {
            const size_t length = strlen(string);
            if(strcmp(string, "stop") == 0)
                check = false;
            else
                printf("Length of the string: %zu.\n", length);
        }
        free(string);
    } while (check);

    return 0;
}

char *handle_input(const int length) {
    char *string = malloc(length);
    if (string) {
        bool stop_loop = false;
        while (!stop_loop) {
            printf("Enter a string: ");
            stop_loop = get_input(string, length);
        }
        return string;
    }
    printf("Memory allocation failed.\n");
    return NULL;
}

bool get_input(char *user_input, const int length) {
    if(fgets(user_input, length, stdin)) {
        if (strchr(user_input, '\n') == NULL) {
            int c = 0;
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Input too long (max %d characters).\n", length-2);
            return false;
        }
        user_input[strcspn(user_input, "\n")] = '\0';
        if (user_input[0] == '\0') {
            printf("Empty input.\n");
            return false;
        }
        return true;
    }
    return false;
}