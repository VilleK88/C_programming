#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int number;
    struct node *next;
} nnode;

char *handle_input();
void add(nnode *node_array, struct node *head, struct node *tail, size_t count, int value);

int main() {
    nnode **node_array = NULL;
    size_t count = 0;
    char *input;
    struct node *head = NULL;
    struct node *tail = NULL;

    do {
        input = handle_input();

        if (strcmp(input, "end") != 0) {
            char *endptr;
            long val = strtol(input, &endptr, 10);
            if (errno != 0 || *endptr != '\0') {
                printf("Invalid input.\n");
            }
            else {
                int value = (int)val;
                add(&node_array, &head, &tail, &count, &value);

                /*nnode *newline = malloc(sizeof *newline);

                newline->next = NULL;
                newline->number = value;

                if (!head)
                    head = tail = newline;
                else {
                    tail->next = newline;
                    tail = newline;
                }

                nnode **tmp = realloc(node_array, (count + 1) * sizeof *node_array);
                node_array = tmp;
                node_array[count++] = head;*/
            }
        }
    } while (strcmp(input, "end") != 0);

    printf("\nNumbers:\n");
    for (nnode *p = head; p; p = p->next) {
        printf("%d ", p->number);
    }

    free(node_array);
    free(input);
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

void add(nnode *node_array, struct node *head, struct node *tail, size_t count, int value) {
    nnode *newline = malloc(sizeof *newline);

    newline->next = NULL;
    newline->number = value;

    if (!head)
        head = tail = newline;
    else {
        tail->next = newline;
        tail = newline;
    }

    nnode **tmp = realloc(node_array, (count + 1) * sizeof *node_array);
    node_array = tmp;
    node_array[count++] = *head;
}