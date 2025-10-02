#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define INPUT_LENGTH 4

char *handle_input(int length);
bool get_input(char *user_input, int length);
void remove_newline(char *user_input);
bool get_nums_from_a_string(const char *string, int *num);
void print_hexadecimal(int num, int rand_num);

int main() {
    bool continue_loop = true;

    srand((unsigned int)time(NULL));

    do {
        char *num_str = handle_input(INPUT_LENGTH);
        int num;
        const bool if_number = get_nums_from_a_string(num_str, &num);
        if (if_number) {
            if (num < 0) {
                continue_loop = false;
            }
            else {
                if (num >= 0 && num <= 15) {
                    const int rand_num = rand() % 100;
                    print_hexadecimal(num, rand_num);
                }
                else if (num > 15) {
                    printf("Number is out of range.\n");
                }
            }
        }
        else {
            printf("Invalid input.\n");
        }

        free(num_str);
    } while (continue_loop);

    return 0;
}

char *handle_input(const int length) {
    char *string = malloc(length);
    if (string) {
        bool stop_loop = false;
        while (!stop_loop) {
            printf("Enter a number: ");
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

bool get_nums_from_a_string(const char *string, int *num) {
    char *num_char = malloc(strlen(string) + 1);

    int j = 0;
    for (int i = 0; string[i] != '\0'; i++) {
        if (isdigit(string[i])) {
            num_char[j++] = string[i];
        }
    }
    num_char[j] = '\0';
    if (j > 0) {
        *num = atoi(num_char);
        if (string[0] == '-') {
            *num = -*num;
        }
        free(num_char);
        return true;
    }

    free(num_char);
    return false;
}

void print_hexadecimal(const int num, const int rand_num) {
    const unsigned int shift_right = rand_num  >> num;
    const unsigned int bits = shift_right & 0x3f;
    printf("Random number hexadecimal: %02x\n", bits);
}