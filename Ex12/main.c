#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void handle_input(char *input_text, char *user_input, int length);
bool get_input(char *user_input, int length);
int count_words(const char* str, const char *word);

int main() {
    char string[82],  word[34];

    do {
        handle_input("Enter a string: ", string, 82);
        handle_input("Enter a word: ", word, 34);
        if (strcmp(word, "stop") != 0 && string[0] != '\0' && word[0] != '\0') {
            const int sum = count_words(string, word);
            printf("%d\n", sum);
        }
    } while (strcmp(word, "stop") != 0);

    return 0;
}

void handle_input(char *input_text, char *user_input, int length) {
    bool continue_loop = false;
    while (!continue_loop) {
        printf("%s", input_text);
        continue_loop = get_input(user_input, length);
    }
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

int count_words(const char* str, const char *word) {
    int sum = 0;
    while ((str = strstr(str, word)) != NULL) {
        sum++;
        str += strlen(word);
    }
    return sum;
}