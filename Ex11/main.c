#include <stdio.h>
#include <string.h>

int replace_char(char *str, const char *repl);
void handle_input(char *description, char *this_text, int this_count);

int main() {
    char text[32], repl[3];

    handle_input("Enter string: ", text, 32);
    handle_input("Enter replace: ", repl, 3);

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
    const int length = (int)strlen(str);
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
    this_text[strcspn(this_text, "\n")] = '\0';
}