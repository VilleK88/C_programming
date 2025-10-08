#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add(int num1, int num2);
void sub(int num1, int num2);
void mul(int num1, int num2);
void division(int num1, int num2);
int get_nums_from_a_string(const char *string);
int get_choice(char *choice);
void remove_newline(char *user_input);

int main() {
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        int count = 0;
        int invalid_position = 0;
        int numbers[2];
        char *str_num = NULL;
        int j = 0;
        char *cmd = NULL;
        for (int i = 0; i < strlen(buffer); i++) {
            if (count < 2) {
                if (buffer[i] != ' ') {
                    char *tmp_str_num = realloc(str_num, j + 2);
                    if (tmp_str_num) {
                        str_num = tmp_str_num;
                        str_num[j++] = buffer[i];
                        str_num[j] = '\0';
                    }
                }
                else {
                    char *endptr;
                    const long val = strtol(str_num, &endptr, 10);
                    if (endptr == str_num || *endptr != '\0') {
                        invalid_position = count+1;
                    }
                    else {
                        numbers[count] = (int)val;
                    }
                    count++;
                    j = 0;
                }
            }
            else {
                if (buffer[i] != ' ') {
                    char *tmp = realloc(cmd, j + 2);
                    if (tmp) {
                        cmd = tmp;
                        cmd[j++] = buffer[i];
                        cmd[j] = '\0';
                    }
                }
            }
        }
        if (invalid_position == 0) {
            const int choice = get_choice(cmd);
            switch (choice) {
                case 1:
                    add(numbers[0], numbers[1]);
                    break;
                case 2:
                    sub(numbers[0], numbers[1]);
                    break;
                case 3:
                    mul(numbers[0], numbers[1]);
                    break;
                case 4:
                    division(numbers[0], numbers[1]);
                    break;
                default:
                    remove_newline(buffer);
                    printf("Input: %s Unknown command: %s\n", buffer, cmd);
                    break;
            }
        }
        else {
            printf("Input: %s Invalid argument in position: %d\n", buffer, invalid_position);
        }

        free(str_num);
        free(cmd);
    }
    else {
        printf("Error");
    }

    return 0;
}

void add(const int num1, const int num2) {
    const int result = num1 + num2;
    printf("%d + %d = %d\n", num1, num2, result);
}

void sub(const int num1, const int num2) {
    const int result = num1 - num2;
    printf("%d - %d = %d\n", num1, num2, result);
}

void mul(const int num1, const int num2) {
    const int result = num1 * num2;
    printf("%d * %d = %d\n", num1, num2, result);
}

void division(const int num1, const int num2) {
    const int result = num1 / num2;
    printf("%d / %d = %d\n", num1, num2, result);
}

int get_choice(char *choice) {
    if (choice) {
        remove_newline(choice);
        const char *choices[] = {"add", "sub", "mul", "div"};
        for (int i = 0; i < 4; i++) {
            if (strcmp(choice, choices[i]) == 0)
                return i+1;
        }
    }
    return -1;
}

void remove_newline(char *user_input) {
    if (user_input[strlen(user_input) - 1] == '\n') {
        user_input[strlen(user_input) - 1] = '\0';
    }
}