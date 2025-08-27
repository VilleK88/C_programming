#include <stdio.h>
#include <string.h>

void handle_input(char *description, char *input, int size);
int count_words(const char* str, const char *word);
void handle_program(char *this_string, char *this_word);

int main() {
    char string[80],  word[80];

    handle_program(string, word);

    return 0;
}

void handle_input(char *description, char *input, const int size) {

    printf("%s", description);
    fgets(input, size, stdin);
    input[strcspn(input, "\n")] = '\0';
}

int count_words(const char* str, const char *word) {
    int sum = 0;

    while ((str = strstr(str, word)) != NULL) {
        sum++;
        str += strlen(word);
    }

    return sum;
}

void handle_program(char *this_string, char *this_word) {
    while (1) {
        handle_input("Enter a string: ", this_string, 80);
        handle_input("Enter a word: ", this_word, 80);

        if (strcmp(this_word, "stop") == 0) break;

        const int sum = count_words(this_string, this_word);
        printf("sum: %d\n", sum);
    }
}