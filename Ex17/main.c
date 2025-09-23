#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define input_length 34

char *handle_input(int length);
bool get_input(char *user_input, int length);
bool password_generator(char *word_out, int array_size, const char *word_in);
const char * const *get_table(void);

int main() {
    int count = 0;
    char **passwords = NULL;
    srand((unsigned int)time(NULL));
    bool continue_loop = true;

    do {
        char *word = handle_input(input_length);
        if (strcmp(word, "stop") != 0) {
            char word_out[strlen(word)];
            const bool successful = password_generator(word_out, 32, word);
            if (successful) {
                char **tmp = realloc(passwords, (size_t)(count+1) * sizeof * passwords);
                if (!tmp) free(tmp);
                else {
                    passwords = tmp;
                    // allocates heap memory and copies word_out
                    passwords[count++] = strdup(word_out);
                    printf("Word in array: %s\n", passwords[count-1]);
                }
            }
        }
        else continue_loop = false;

        free(word);
    } while (continue_loop);

    free(passwords);
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
        user_input[strcspn(user_input, "\n")] = '\0';
        if (user_input[0] == '\0') {
            printf("Empty input.\n");
            return false;
        }
        return true;
    }
    return false;
}

bool password_generator(char *word_out, int const array_size, const char *word_in) {
    const char * const *table = get_table();
    const size_t word_length = strlen(word_in);
    const size_t max_length = word_length * 2 + 1;

    if (max_length <= array_size) {
        char new_word[max_length+1];
        bool rotation = true;
        int j = 0;
        for (int i = 0; i <= max_length; i++) {
            const int randomTable = rand() % 4;
            const size_t len = strlen(table[randomTable]);
            const int randomIndex = rand() % (int)len;
            const char randomChar = table[randomTable][randomIndex];
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

const char * const *get_table(void) {
    static const char numbers[] = "0123456789", symbols[] = "!@#$^&*?";
    static const char letter[] = "abcdefghijklmnoqprstuvwyzx";
    static const char LETTER[] = "ABCDEFGHIJKLMNOQPRSTUYWVZX";
    static const char * const table[] = {numbers, symbols, letter, LETTER};
    return table;
}