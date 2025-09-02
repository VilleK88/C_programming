#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int number;
    struct node *next;
} nnode;

char *handle_input();
struct node *add_to_llist(struct node *head, int value);
void print_numbers(struct node *head);

int main() {
    nnode **node_array = NULL;
    size_t count = 0;
    char *input;
    struct node *head = NULL;

    do {
        printf("Enter integer: ");
        input = handle_input();
        char *endptr;
        long val = strtol(input, &endptr, 10);
        if (*endptr == '\0') {
            int value = (int)val;
            nnode *tmp = realloc(node_array, (count + 1) * sizeof * node_array);
            node_array = tmp;
            head = add_to_llist(head, value);
            node_array[count++] = head;
        }

    } while (strcmp(input, "end") != 0);

    print_numbers(head);

    free(input);
    free(node_array);
    return 0;
}

char *handle_input() {
    char *string = malloc(32);
    if (!string) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    printf("Enter a integer or 'end' to stop: ");
    if (!fgets(string, 32, stdin)) {
        free(string);
        return NULL;
    }

    string[strcspn(string, "\n")] = '\0';

    return string;
}

struct node *add_to_llist(struct node *head, int value) {
    nnode *newline = malloc(sizeof(*newline));
    newline->next = NULL;
    newline->number = value;

    if (!head)
        return newline;

    struct node *tail = head;
    while (tail->next) tail = tail->next;
    tail->next = newline;

    return head;
}

void print_numbers(struct node *head) {
    printf("Numbers:\n");
    for (nnode *p = head; p; p = p->next) {
        printf("%d ", p->number);
    }
}