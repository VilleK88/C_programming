#include <stdio.h> // printf, fgets, scanf
#include <stdlib.h> // malloc, realloc, free, atoi
#include <string.h> // strcmp, strcspn, strlen, strstr

char *handle_input();

int main() {
    FILE *file;
    int *numbers = NULL;
    int count = 0, capacity = 0;

    printf("Enter a filename: ");
    char *filename = handle_input();
    if (filename == NULL) {
        free(filename);
        return 0;
    }

    if ((file = fopen(filename, "r")) == NULL) {
        printf("File not found!\n");
        free(filename);
        return 0;
    }

    int temp;
    while (fscanf(file, "%d", &temp) == 1) {
        // Increase capacity if needed
        if (count <= capacity) {
            capacity = (capacity == 0) ? 4 : capacity * 2;
            numbers = realloc(numbers, capacity * sizeof(int));
            if (numbers == NULL) {
                printf("Memory allocation failed.\n");
                fclose(file);
                return 0;
            }
        }
        numbers[count++] = temp;
    }
    fclose(file);

    printf("%d numbers found:\n", count);
    for (int i = 0; i < count; i++) printf("%d ", numbers[i]);

    free(numbers);
    free(filename);
    return 0;
}

char *handle_input() {
    char *string = malloc(32);
    if (!string) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    if (!fgets(string, 32, stdin)) {
        free(string);
        return NULL;
    }

    string[strcspn(string, "\n")] = '\0';

    return string;
}