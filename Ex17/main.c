#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

char *handle_input();
char *input_warning_and_free_memory(char *error_msg, char *string);
bool password_generator(char *word_out, int array_size, const char *word_in);
const char * const *get_table(void);

int main() {
    int count = 0;
    char **passwords = NULL;
    srand((unsigned int)time(NULL));
    bool continue_loop = true;

    do {
        printf("Enter password: ");
        char *word = handle_input();

        if (word != NULL) {

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
        }

        free(word);
    } while (continue_loop);

    free(passwords);
    return 0;
}

char *handle_input() {
    char *string = malloc(32);

    if (string) {
        if (fgets(string, 32, stdin)) {
            if (strchr(string, '\n') == NULL) {
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF){}
                return input_warning_and_free_memory("Input too long (max 32 characters).\n", string);
            }
            // replaces the first '\n' in the string with '\0' to remove the newline
            string[strcspn(string, "\n")] = '\0';

            if (string[0] == '\0')
                return input_warning_and_free_memory("Empty input.\n", string);
        }
        else
            return input_warning_and_free_memory("The input reading failed (EOF or input error).\n", string);
    }
    else
        return input_warning_and_free_memory("Memory allocation failed.\n", string);

    return string;
}

char *input_warning_and_free_memory(char *error_msg, char *string) {
    printf("%s", error_msg);
    free(string);
    return NULL;
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