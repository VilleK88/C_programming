#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

int filter_alpha(char *str, int max_len, void (*get)(char));

void my_getchar(char c);

int main() {
    char *str = {"Testing"};
    int count = filter_alpha(str, 7, my_getchar);

    printf("Characters read: %d\n", count);
    printf("Stored string length: %lu\n", strlen(str));
    printf("Stored string contents:\n%s\n", str);

    return 0;
}

// isalpha()
int filter_alpha(char *str, int max_len, void (*get)(char)) {
    char *new_str[max_len];
    int len = (int) strlen(str);
    //printf("len: %d\n", len);

    int index = 0;
    for (int i = 0; i < max_len; i++) {
        //printf("%c", str[i]);
        if (isalpha(str[i])) {
            new_str[index] += str[i];
        }
    }

    printf("%s\n", *new_str);

    printf("\n\n");


    return 0;
}

void my_getchar(char c) {

}
