#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define INPUT_LENGTH 34

char *handle_input(int length);
bool get_input(char *user_input, int length);
void remove_newline(char *user_input);
bool password_generator(char *word_out, int array_size, const char *word_in);

int main() {
    srand((unsigned int)time(NULL));
    bool continue_loop = true;

    do {
        char *word = handle_input(INPUT_LENGTH);
        if (strcmp(word, "stop") != 0) {
            const int word_len = (int)strlen(word) * 2 + 1;
            char word_out[word_len];
            const bool successful = password_generator(word_out, word_len, word);
            if (successful) {
                printf("Word in array: %s\n", word_out);
            }
        }
        else continue_loop = false;

        free(word);
    } while (continue_loop);

    return 0;
}

char *handle_input(const int length) {
    char *string = malloc(length);
    if (string) {
        bool stop_loop = false;
        while (!stop_loop) {
            printf("Enter password: ");
            stop_loop = get_input(string, length);
        }
        return string;
    }
    printf("Memory allocation failed.\n");
    exit(EXIT_FAILURE);
}

bool get_input(char *user_input, const int length) {
    if(fgets(user_input, length, stdin)) {
        if (strchr(user_input, '\n') == NULL) {
            int c = 0;
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Input too long (max %d characters).\n", length-2);
            return false;
        }
        remove_newline(user_input);
        if (user_input[0] == '\0') {
            printf("Empty input.\n");
            return false;
        }
        return true;
    }
    return false;
}

void remove_newline(char *user_input) {
    if (user_input[strlen(user_input) - 1] == '\n') {
        user_input[strlen(user_input) - 1] = '\0';
    }
}

bool password_generator(char *word_out, int const array_size, const char *word_in) {
    if (INPUT_LENGTH >= array_size) {
        char new_word[INPUT_LENGTH + 1];
        bool rotation = true;
        int j = 0;
        for (int i = 0; i <= INPUT_LENGTH; i++) {
            const int random_num = 33 + rand() % (126 - 33 + 1);
            const char randomChar = (char)random_num;
            if (rotation) {
                new_word[i] = randomChar;
                rotation = false;
            }
            else {
                new_word[i] = word_in[j++];
                rotation = true;
            }
        }
        strcpy(word_out, new_word);
        return true;
    }
    return false;
}