#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FILENAME_LENGTH 34

typedef struct menu_item_ {
    char name[50];
    double price;
} menu_item;

char *get_filename();
bool get_input(char *user_input);
FILE *open_file(char *this_filename);
void read_file(FILE *this_file, menu_item *items, int *count, int capacity);
void print_menu(menu_item *items, int count);

int main() {
    int count = 0;
    struct menu_item_ menu_items[40];

    char *filename = get_filename();
    FILE *file = open_file(filename);
    read_file(file, menu_items, &count, sizeof(menu_items) / sizeof(menu_items[0]));
    print_menu(menu_items, count);

    free(filename);
    return 0;
}

char *get_filename() {
    char *string = malloc(FILENAME_LENGTH);
    if (string) {
        bool stop_loop = false;
        while (!stop_loop) {
            printf("Enter a filename: ");
            stop_loop = get_input(string);
        }
        return string;
    }
    printf("Memory allocation failed.\n");
    exit(EXIT_FAILURE);
}

bool get_input(char *user_input) {
    if(fgets(user_input, FILENAME_LENGTH, stdin)) {
        if (strchr(user_input, '\n') == NULL) {
            int c = 0;
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Input too long (max %d characters).\n", FILENAME_LENGTH-2);
            return false;
        }
        user_input[strcspn(user_input, "\n\r")] = '\0';
        if (user_input[0] == '\0') {
            printf("Empty input.\n");
            return false;
        }
        return true;
    }
    return false;
}

FILE *open_file(char *this_filename) {
    FILE * file;
    if ((file = fopen(this_filename, "r")) == NULL) {
        fprintf(stderr, "Error: could not open file: '%s'\n", this_filename);
        exit(EXIT_FAILURE);
    }
    return file;
}

void read_file(FILE *this_file, menu_item *items, int *count, const int capacity) {
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

void print_menu(menu_item *items, const int count) {
    printf("Menu:\n");
    for (int i = 0; i < count; i++) {
        printf("%8.2f %s\n", items[i].price, items[i].name);
    }
}