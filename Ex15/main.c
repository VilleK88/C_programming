#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct menu_item_ {
    char name[50];
    double price;
} menu_item;

char *handle_input();
FILE *open_file(char *this_filename);
void read_file(FILE *this_file, menu_item *items, int *count, int capacity);
void print_menu(menu_item *items, int count);

int main() {
    int count = 0;
    struct menu_item_ menu_items[40];

    char *filename = handle_input();
    FILE *file = open_file(filename);
    read_file(file, menu_items, &count, sizeof(menu_items) / sizeof(menu_items[0]));
    print_menu(menu_items, count);

    return 0;
}

char *handle_input() {
    char *string = malloc(32);
    if (!string) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    printf("Enter a filename: ");
    if (!fgets(string, 32, stdin)) {
        free(string);
        return NULL;
    }

    string[strcspn(string, "\n")] = '\0';

    return string;
}

FILE *open_file(char *this_filename) {
    FILE * file;

    if ((file = fopen(this_filename, "r")) == NULL) {
        fprintf(stderr, "Error: could not open file: '%s'\n", this_filename);
        free(this_filename);
        exit(EXIT_FAILURE);
    }

    return file;
}

void read_file(FILE *this_file, menu_item *items, int *count, int capacity) {
    char line[200];

    while (fgets(line, sizeof(line), this_file) != NULL && *count < capacity) {
        char *semicolon = strchr(line, ';');
        if (semicolon) {
            *semicolon = '\0';
            strncpy(items[*count].name, line, sizeof(items[*count].name));
            items[*count].name[sizeof(items[*count].name) - 1] = '\0';
            items[*count].price = atof(semicolon + 1);
            (*count)++;
        }
    }

    fclose(this_file);
}

void print_menu(menu_item *items, int count) {
    printf("Menu:\n");
    for (int i = 0; i < count; i++) {
        printf("%8.2f %s\n", items[i].price, items[i].name);
    }
}