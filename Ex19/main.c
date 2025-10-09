#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FILENAME_LENGTH 34
#define LINE_LENGTH 200

typedef struct menu_item_ {
    char name[50];
    double price;
} menu_item;

char *handle_input(int length, char *text);
bool get_input(char *user_input, int length);
void remove_newline(char *user_input);
FILE *open_file(char *this_filename);
void read_file(FILE *this_file, menu_item *items, int *count, int capacity);
void add_to_items(menu_item *items, int *count, const char *line, char *semicolon);
void print_order_info();
void choose_sort_order(menu_item *items, const int *count);
int get_choice();
bool make_the_choice(char *string, int choice, menu_item *items, const int *count);
int sort_by_name(const void *a, const void *b);
int sort_by_price(const void *a, const void *b);
void print_menu(menu_item *items, int count);

int main() {
    int count = 0;
    struct menu_item_ menu_items[40];

    char *filename = handle_input(FILENAME_LENGTH, "Enter a filename: ");
    FILE *file = open_file(filename);
    read_file(file, menu_items, &count, sizeof(menu_items) / sizeof(menu_items[0]));
    choose_sort_order(menu_items, &count);
    print_menu(menu_items, count);

    free(filename);
    return 0;
}

char *handle_input(const int length, char *text) {
    char *string = malloc(length);
    if (string) {
        bool stop_loop = false;
        while (!stop_loop) {
            printf("%s", text);
            stop_loop = get_input(string, length);
        }
        return string;
    }
    printf("Memory allocation failed.\n");
    exit(EXIT_FAILURE);
}

bool get_input(char *user_input, const int length) {
    if(fgets(user_input, length, stdin)) {
        if (strchr(user_input, '\n') == NULL) {
            int c = 0;
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Input too long (max %d characters).\n", length-2);
            return false;
        }
        remove_newline(user_input);
        if (user_input[0] == '\0') {
            printf("Empty input.\n");
            return false;
        }
        return true;
    }
    return false;
}

void remove_newline(char *user_input) {
    if (user_input[strlen(user_input) - 1] == '\n') {
        user_input[strlen(user_input) - 1] = '\0';
    }
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
    char line[LINE_LENGTH];
    while (fgets(line, sizeof(line), this_file) != NULL && *count < capacity) {
        char *semicolon = strchr(line, ';');
        if (semicolon)
            add_to_items(items, count, line, semicolon);
    }
    fclose(this_file);
}

void add_to_items(menu_item *items, int *count, const char *line, char *semicolon) {
    *semicolon = '\0';
    strncpy(items[*count].name, line, sizeof(items[*count].name));
    items[*count].name[sizeof(items[*count].name) - 1] = '\0';
    items[*count].price = atof(semicolon + 1);
    (*count)++;
}

void print_order_info() {
    printf("Choose sorting order by name or price.\n");
    printf("1) name\n2) price\n");
}

void choose_sort_order(menu_item *items, const int *count) {
    bool continue_loop = true;
    print_order_info();
    do {
        const int choice = get_choice();
        switch (choice) {
            case 1:
                continue_loop = make_the_choice("Sort by name.\n", 1, items, count);
                break;
            case 2:
                continue_loop = make_the_choice("Sort by price.\n", 2, items, count);
                break;
            default:
                break;
        }
    } while (continue_loop);
}

int get_choice() {
    long int value = 0;
    bool continue_loop = true;

    do {
        char *choice = handle_input(34, "Enter choice: ");
        char *endPtr;
        const long int val = strtol(choice, &endPtr, 10);
        if (*endPtr == '\0' && (val == 1 || val == 2)) {
            value = val;
            continue_loop = false;
        }
        else {
            if (*endPtr != '\0')
                printf("Invalid input: %s\n", choice);
            else
                printf("Input out of range: %d\n", (int)val);
            print_order_info();
        }
        free(choice);
    } while (continue_loop);

    return value;
}

bool make_the_choice(char *string, const int choice, menu_item *items, const int *count) {
    printf("%s", string);
    if (choice == 1)
        qsort(items, *count, sizeof(menu_item), sort_by_name);
    else if (choice == 2)
        qsort(items, *count, sizeof(menu_item), sort_by_price);
    return false;
}

int sort_by_name(const void *a, const void *b) {
    return strcmp(((struct menu_item_*)a)->name, ((struct menu_item_*)b)->name);
}

int sort_by_price(const void *a, const void *b) {
    const menu_item *item_a = a;
    const menu_item *item_b = b;
    return (item_a->price > item_b->price) - (item_a->price < item_b->price);
}

void print_menu(menu_item *items, const int count) {
    printf("Menu:\n");
    for (int i = 0; i < count; i++) {
        printf("%8.2f %s\n", items[i].price, items[i].name);
    }
}