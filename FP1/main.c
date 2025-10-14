#include <stdio.h>

int print_string(const char *str, void (*printer)(char));
void print_char(char c);

int main() {
    const char *str = "hello";
    int count = print_string(str, print_char);
    printf(":%d\n", count);

    const char *str2 = "abc123 XYZ!";
    int count2 = print_string(str2, print_char);
    printf(":%d\n", count2);

    return 0;
}

int print_string(const char *str, void (*printer)(char)) {
    int count = 0;
    while (*str) {
        printer(*str++);
        count++;
    }
    return count;
}

void print_char(const char c) {
    printf("%c", c);
}