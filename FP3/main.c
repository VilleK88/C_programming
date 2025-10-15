#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>

int filter_alpha(char *str, int max_len, char (*get)(void));

char my_getchar(void);

int main() {
    char str[39] = {0};
    int count = filter_alpha(str, 39, my_getchar);

    printf("Characters read: %d\n", count);
    printf("Stored string length: %lu\n", strlen(str));
    printf("Stored string contents:\n%s\n", str);

    //char *test_str = "I'm too big for this testcase, I'm not going to fit in to the buffer. Sad.";
    //printf("test_str len: %d\n", (int)strlen(test_str));

    return 0;
}

int filter_alpha(char *str, int max_len, char (*get)(void)) {
    char *new_str = NULL;
    bool continue_loop = true;
    int size = 0;
    int count = 0;

    do {
        char c = get();
        //printf("c: %c, count: %d\n", c, count+1);
        if (c != 0) {
            if (isalpha(c) || c == '\n') {
                //printf("c: %c, count: %d\n", c, count);
                count ++;
            }

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
                continue_loop = false;
            }
        }

    } while (continue_loop);

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