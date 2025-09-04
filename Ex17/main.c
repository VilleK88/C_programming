#include <stdio.h> // printf, fgets, scanf
#include <stdlib.h> // malloc, realloc, free, atoi
#include <string.h> // strcmp, strlen, strcspn, strstr, strcpy
#include <stdbool.h>
#include <time.h>

char *handle_input();
char *input_warning_and_free_memory(char *error_msg, char *string);
char *handle_input_error(char **this_string);
bool password_generator(char *word_out, int this_size, char *word_in);

int main() {
    int count = 0;
    char *passwords[3][32];
    srand((unsigned int)time(NULL));
    bool continue_loop = true;

    do {
        printf("Enter password: ");
        char *word = handle_input();
        if (word != NULL) {
            if (strcmp(word, "stop") != 0) {
                const size_t size = sizeof(passwords) / sizeof(passwords[0]);
                char word_out[strlen(word)];
                const bool successful = password_generator(&word_out, size, word);
                if (successful) {
                    printf("Word out: %s\n", word_out);
                    *passwords[count++] = word_out;
                    printf("Word in array: %s\n", *passwords[count-1]);
                }
            }
            else continue_loop = false;
        }
        free(word);
    } while (continue_loop);

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

bool password_generator(char *word_out, int const this_size, char *word_in) {
    char numbers[] = "0123456789", symbols[] = "!@#$^&*?";
    char letter[] = "abcdefghijklmnoqprstuvwyzx";
    char LETTER[] = "ABCDEFGHIJKLMNOQPRSTUYWVZX";
    char *table[] = {numbers, symbols, letter, LETTER};

    if (this_size <= 3) {
        int word_length = strlen(word_in);
        int max_length = word_length * 2 + 1;
        printf("Word is: %s\n", word_in);
        printf("Word length is: %d\n", word_length);
        printf("this_size is: %d\n", this_size);
        if (max_length <= 32) {
            char new_word[max_length+1];
            bool rotation = true;
            int count = 0;
            for (int i = 0; i <= max_length; i++) {
                const int randomTable = rand() % 4;
                const int len = strlen(table[randomTable]);
                const int randomIndex = rand() % len;
                const char randomChar = table[randomTable][randomIndex];
                if (rotation) {
                    new_word[i] = randomChar;
                    rotation = false;
                }
                else {
                    new_word[i] = word_in[count++];
                    rotation = true;
                }
                printf("word in i: %c\n", word_in[i]);
            }
            printf("New word inside function: %s\n", new_word);
            strcpy(word_out, new_word);
            printf("Word length is less than 32.\n");
            return true;
        }

    }

    return false;
}