#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int handle_input();

int main() {
    int num;

    do {
        num = handle_input();
        if (num != 0) {
            printf("Number: %d\n", num);
        }
    } while (num != 0);

    return 0;
}

int handle_input() {
    int value;
    printf("Enter a number: ");
    if (scanf_s("%d", &value) != 1) {
        while (getchar() != '\n'){}
        printf("Invalid input.\n");
    }
    return value;
}