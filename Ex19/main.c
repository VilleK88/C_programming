#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define filename_length 34

typedef struct menu_item_ {
    char name[50];
    double price;
} menu_item;

char *get_filename(int length);
bool get_input(char *user_input, int length);
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

    char *filename = get_filename(filename_length);
    if (filename) {
        FILE *file = open_file(filename);
        read_file(file, menu_items, &count, sizeof(menu_items) / sizeof(menu_items[0]));
        choose_sort_order(menu_items, &count);
        print_menu(menu_items, count);
    }

    free(filename);
    return 0;
}

char *get_filename(const int length) {
    char *string = malloc(length);
    if (string) {
        bool stop_loop = false;
        while (!stop_loop) {
            printf("Enter a string: ");
            stop_loop = get_input(string, length);
        }
        return string;
    }
    printf("Memory allocation failed.\n");
    return NULL;
}

bool get_input(char *user_input, const int length) {
    if(fgets(user_input, length, stdin)) {
        if (strchr(user_input, '\n') == NULL) {
            int c = 0;
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Input too long (max %d characters).\n", length-2);
            return false;
        }
        user_input[strcspn(user_input, "\n")] = '\0';
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
        printf("Enter choice: ");
        const int choice = get_choice();
        switch (choice) {
            case 1:
                continue_loop = make_the_choice("Sort by name.\n", 1, items, count);
                break;
            case 2:
                continue_loop = make_the_choice("Sort by price.\n", 2, items, count);
                break;
            default:
                printf("Choice is out of range.\n");
                break;
        }
    } while (continue_loop);
}

int get_choice() {
    int value;

    if (scanf_s("%d", &value) != 1) {
        while (getchar() != '\n'){}
        printf("Invalid input.\n");
        return 0;
    }

    return value;
}

bool make_the_choice(char *string, int choice, menu_item *items, const int *count) {
    printf("%s", string);
    if (choice == 1)
        qsort(items, *count, sizeof(menu_item), sort_by_name);
    else if (choice == 2)
        qsort(items, *count, sizeof(menu_item), sort_by_price);
    return false;
}

int sort_by_name(const void *a, const void *b) {
    const menu_item *item_a = a;
    const menu_item *item_b = b;
    return strcmp(item_a->name, item_b->name);
}

int sort_by_price(const void *a, const void *b) {
    const menu_item *item_a = a;
    const menu_item *item_b = b;

    if (item_a->price < item_b->price)
        return -1;
    if (item_a->price > item_b->price)
        return 1;

    return 0;
}

void print_menu(menu_item *items, const int count) {
    printf("Menu:\n");
    for (int i = 0; i < count; i++) {
        printf("%8.2f %s\n", items[i].price, items[i].name);
    }
}