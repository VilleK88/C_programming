#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int replace_char(char *str, const char *repl);
bool get_input(char *user_input, int length);
void handle_input(char *input_text, char *user_input, int length);

int main() {
    char text[34], repl[4];

    handle_input("Enter string: ", text, 34);
    handle_input("Enter replace: ", repl, 4);

    const int count = replace_char(text, repl);

    if (count <= 0) {
        printf("String was not modified.\n");
    }
    else {
        printf("%d\n", count);
        printf("%s", text);
    }

    return 0;
}

int replace_char(char *str, const char *repl) {
    if (strlen(repl) < 2) return 0;
    int count = 0;
    for (int i = 0; i < (int)strlen(str); i++) {
        if (str[i] == repl[0]) {
            str[i] = repl[1];
            count++;
        }
    }
    return count;
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

void handle_input(char *input_text, char *user_input, const int length) {
    bool continue_loop = false;
    while (!continue_loop) {
        printf("%s", input_text);
        continue_loop = get_input(user_input, length);
    }
}