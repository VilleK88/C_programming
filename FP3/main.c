#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>

int filter_alpha(char *str, int max_len, char (*get)(void));
char my_getchar(void);

int main() {
    char str[40] = {0};
    //int count = filter_alpha(str, 40, my_getchar);

    //printf("Characters read: %d\n", count);
    //printf("Stored string length: %lu\n", strlen(str));
    //printf("Stored string contents:\n%s\n", str);


    int second_count = 0;

    char s_str[50] = {0};
    do {
        second_count = filter_alpha(s_str, 50, my_getchar);
        printf("%d:%lu:%s\n", second_count, strlen(str), str);
    } while (second_count > 0);

    return 0;
}

int filter_alpha(char *str, int max_len, char (*get)(void)) {
    char *new_str = NULL;
    bool continue_loop = true;
    int size = 0;
    int count = 0;

    do {
        char c = get();
        if (c != 0) {
            count ++;

            if (c != '\n' && c != '\r') {
                if (isalpha(c) && c != ' ' && size <= max_len - 1) {
                    char *temp = realloc(new_str, (size + 2) * sizeof(char));
                    if (temp) {
                        new_str = temp;
                        new_str[size++] = c;
                        new_str[size] = '\0';
                    }
                    else {
                        printf("Memory allocation failed.\n");
                        exit(EXIT_FAILURE);
                    }
                }
            }
            else {
                if (count == 1) {
                    count = 0;
                }
                continue_loop = false;
            }
        }
        else {
            continue_loop = false;
        }

    } while (continue_loop);

    if (new_str) {
        strncpy(str, new_str, max_len - 1);
        str[max_len] = '\0';
        free(new_str);
    }
    else {
        str[0] = '\0';
    }

    return count;
}

char my_getchar(void) {
    int c = getchar();
    if (c == EOF) return 0;
    return (char)c;
}