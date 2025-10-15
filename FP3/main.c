#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

int filter_alpha(char *str, int max_len, char (*get)(void));

char my_getchar(void);

int main() {
    char str[43] = {0};
    int count = filter_alpha(str, 43, my_getchar);

    printf("Characters read: %d\n", count);
    printf("Stored string length: %lu\n", strlen(str));
    printf("Stored string contents:\n%s\n", str);

    return 0;
}

int filter_alpha(char *str, int max_len, char (*get)(void)) {
    char *new_str = NULL;
    int size = 0;
    int count = 0;

    for (int i = 0; i <= max_len; i++) {
        char c = get();
        if (c != 0) {
            count ++;

            if (c != '\n') {
                if (isalpha(c) && c != ' ' && size <= max_len) {
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
                break;
            }
        }
    }

    if (new_str) {
        strncpy(str, new_str, max_len);
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