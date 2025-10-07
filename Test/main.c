#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

int add(int num1, int num2);
int sub(int num1, int num2);
int mul(int num1, int num2);
int division(int num1, int num2);
int get_nums_from_a_string(const char *string);

int main() {
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        int count = 0;
        int numbers[2];
        int result = 0;
        char *str_num = NULL;
        int j = 0;
        char *cmd = NULL;
        for (int i = 0; i < strlen(buffer); i++) {
            if (count < 2) {
                if (buffer[i] != ' ') {
                    //str_num[j++] = buffer[i];
                    char *tmp_str_num = realloc(str_num, j + 2);
                    if (!tmp_str_num) {
                        free(str_num);
                    }
                    str_num = tmp_str_num;
                    str_num[j++] = buffer[i];
                    str_num[j] = '\0';
                }
                else {
                    numbers[count++] = atoi(str_num);
                    j = 0;
                }
            }
            else {
                if (buffer[i] != ' ') {
                    char *tmp = realloc(cmd, j + 2);
                    if (!tmp) {
                        free(cmd);
                    }
                    cmd = tmp;
                    cmd[j++] = buffer[i];
                    cmd[j] = '\0';
                }
            }
        }
        printf("%d + %d %s\n", numbers[0], numbers[1], cmd);
    }
    else {
        printf("Error");
    }

    return 0;
}

int add(int num1, int num2) {

}

int sub(int num1, int num2) {

}

int mul(int num1, int num2) {

}

int division(int num1, int num2) {

}