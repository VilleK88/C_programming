#include <stdio.h>
#include <string.h>

int replace_char(char *str, const char *repl);
void handle_input(char *description, char *this_text, int this_count);
void handle_program(char *this_text, char *this_repl);
void trim_newline(char *input);

int main() {
    char text[80], repl[3];
    handle_program(text, repl);

    return 0;
}

int replace_char(char *str, const char *repl) {
    int length = (int)strlen(str);
    int count = 0;

    if (strlen(repl) < 2) return 0;

    for (int i = 0; i < length; i++) {
        if (str[i] == repl[0]) {
            str[i] = repl[1];
            count++;
        }
    }

    if (count <= 0) return 0;

    return count;
}

void handle_input(char *description, char *this_text, int this_count) {
    printf("%s", description);
    fgets(this_text, this_count, stdin);
    trim_newline(this_text);
}

void handle_program(char *this_text, char *this_repl) {
    handle_input("Enter string: ", this_text, 80);
    handle_input("Enter replace: ", this_repl, 3);

    const int count = replace_char(this_text, this_repl);

    if (count <= 0) {
        printf("String was not modified.\n");
    }
    else {
        printf("%d\n", count);
        printf("%s", this_text);
    }
}

void trim_newline(char *input) {
    input[strcspn(input, "\n")] = '\0';
}