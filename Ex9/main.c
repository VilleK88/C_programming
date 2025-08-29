#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int handle_input();
int *initialize_array();
int find_first(const unsigned int *array, unsigned int what);
void handle_program(int *array);

int main() {
    srand((unsigned)time(NULL));

    int *array = initialize_array();
    handle_program(array);

    free(array);
    return 0;
}

int handle_input() {
    int value;

    if (scanf("%d", &value) != 1) {
        while (getchar() != '\n');
        printf("Invalid input.\n");
        return 0;
    }

    return value;
}

int *initialize_array() {
    int *this_array = malloc(20 * sizeof(int));
    if (this_array == NULL) {
        printf("Memory allocation failed.\n");
        return 0;
    }

    for (int i = 0; i < 19; i++) {
        this_array[i] = rand() % 20 + 1;
        printf("%d\n", this_array[i]);
    }
    this_array[19] = 0;

    return this_array;
}

int find_first(const unsigned int *array, unsigned int what) {
    for (int i = 0; array[i] != 0; i++) {
        if (array[i] == what)
            return i;
    }
    return -1;
}

void handle_program(int *array) {
    int num = 0;

    do {
        printf("Enter a number to search for or zero to stop: ");
        num = handle_input();
        int value = find_first(array, num);
        if (value == -1)
            printf("Not found.\n");
        else
            printf("Found at index: %d\n", value);
    } while (num != 0);
}