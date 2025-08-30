#include <stdio.h>
#include <string.h>

void handle_input(char *description, char *input, int size);
int count_words(const char* str, const char *word);

int main() {
    char string[80],  word[80];

    do {
        handle_input("Enter a string: ", string, 80);
        handle_input("Enter a word: ", word, 80);
        if (strcmp(word, "stop") != 0) {
            const int sum = count_words(string, word);
            printf("sum: %d\n", sum);
        }
    } while (strcmp(word, "stop") != 0);

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