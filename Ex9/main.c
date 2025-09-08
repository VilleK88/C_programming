#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int handle_input();
unsigned int *initialize_array();
int find_first(const unsigned int *array, unsigned int what);

int main() {
    int num = 0;
    srand((unsigned)time(NULL));

    unsigned int *array = initialize_array();

    do {
        printf("Enter a number to search for or zero to stop: ");
        num = handle_input();
        const int value = find_first(array, num);
        if (value == -1)
            printf("Not found.\n");
        else
            printf("Found at index: %d\n", value);
    } while (num != 0);

    free(array);
    return 0;
}

int handle_input() {
    int value;

    if (scanf_s("%d", &value) != 1) {
        while (getchar() != '\n'){}
        printf("Invalid input.\n");
        return -2;
    }

    return value;
}

unsigned int *initialize_array() {
    unsigned int *this_array = malloc(20 * sizeof(int));
    if (this_array == NULL) {
        printf("Memory allocation failed.\n");
        return 0;
    }

    for (int i = 0; i < 19; i++) {
        this_array[i] = (unsigned int)(rand() % 20 + 1);
        printf("%d\n", this_array[i]);
    }

    this_array[19] = 0;
    return this_array;
}

int find_first(const unsigned int *array, const unsigned int what) {
    if (array != NULL) {
        for (int i = 0; array[i] != 0; i++) {
            if (array[i] == what)
                return i;
        }
    }
    return -1;
}