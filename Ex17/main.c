#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

char *handle_input();
char *input_warning_and_free_memory(char *error_msg, char *string);
//char *handle_input_error(char **this_string);
bool password_generator(char *word_out, int array_size, char *word_in);
void add_password(char *this_passwords, char *this_word, int *this_count);

int main() {
    int count = 0;
    //char *passwords[3][32];
    char **passwords = NULL;
    srand((unsigned int)time(NULL));
    bool continue_loop = true;

    do {
        printf("Enter password: ");
        char *word = handle_input();
        if (word != NULL) {
            if (strcmp(word, "stop") != 0) {
                char word_out[strlen(word)];
                const bool successful = password_generator(&word_out, 32, word);
                if (successful) {
                    char **tmp = realloc(passwords, (size_t)(count+1) * sizeof * passwords);
                    if (!tmp)
                        free(tmp);
                    else {
                        passwords = tmp;
                        // allocates heap memory and copies word_out
                        passwords[count++] = strdup(word_out);
                    }
                    printf("Word in array: %s\n", passwords[count-1]);
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

bool password_generator(char *word_out, int const array_size, char *word_in) {
    const char numbers[] = "0123456789", symbols[] = "!@#$^&*?";
    const char letter[] = "abcdefghijklmnoqprstuvwyzx";
    const char LETTER[] = "ABCDEFGHIJKLMNOQPRSTUYWVZX";
    const char *table[] = {numbers, symbols, letter, LETTER};

    int word_length = strlen(word_in);
    int max_length = word_length * 2 + 1;
    if (max_length <= array_size) {
        char new_word[max_length+1];
        bool rotation = true;
        int j = 0;
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
                new_word[i] = word_in[j++];
                rotation = true;
            }
            //printf("word in i: %c\n", word_in[i]);
        }
        //printf("New word inside function: %s\n", new_word);
        strcpy(word_out, new_word);
        //printf("Word length is less than 32.\n");
        return true;
    }
    return false;
}

void add_password(char *this_passwords, char *this_word, int *this_count) {
    //printf("This word: %s\n", this_word);
    //printf("This count: %d\n", *this_count);
    //printf("This passwords: %s\n", this_passwords);

}