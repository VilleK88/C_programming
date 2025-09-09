#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *initialize_array(int this_count);
void print_numbers(const int *this_array, int this_count);

int main() {
    const int count = 15;
    srand((unsigned)time(NULL));

    int *numbers = initialize_array(count);
    print_numbers(numbers, count);

    free(numbers);
    return 0;
}

int *initialize_array(const int this_count) {
    int *this_array = malloc(this_count * sizeof(int));
    if (!this_array) {
        printf("Memory allocation failed.\n");
        return 0;
    }

    for (int i = 0; i < this_count; i++) this_array[i] = rand() % this_count + 1;

    return this_array;
}

void print_numbers(const int *this_array, const int this_count) {
    if (this_array != NULL)
        for (int i = 0; i < this_count; i++)
            printf("%8d\n", this_array[i]);
}