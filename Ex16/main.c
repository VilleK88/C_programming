#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node {
    int number;
    struct node *next;
} nnode;

char *handle_input();
void update_list_and_array(struct node ***node_array, size_t *count, struct node **head, long val);
struct node *append_node(struct node *head, int value);
void print_numbers(struct node *head);
char *input_warning_and_free_memory(char *description, char* string);

int main() {
    nnode **node_array = NULL;
    size_t count = 0;
    char *input;
    struct node *head = NULL;
    bool check = true;

    do {
        printf("Enter integer: ");
        input = handle_input();
        if (input != NULL) {
            char *parse_end;
            // Muuntaa input-merkkijonon long-luvuksi (desimaalina) ja tallettaa osoittimen siihen kohtaan,
            // mihin asti luvun lukeminen onnistui (parse_end osoittaa siihen merkkiin).
            const long val = strtol(input, &parse_end, 10);
            if (*parse_end == '\0')
                update_list_and_array(&node_array, &count, &head, val);
            else if(strcmp(input, "end") == 0)
                check = false;
            else
                printf("Invalid input.\n");
        }

    } while (check == true);

    print_numbers(head);

    free(input);
    free(node_array);
    return 0;
}

char *handle_input() {
    char *string = malloc(32);
    if (!string)
        return input_warning_and_free_memory("Memory allocation failed.\n", string);

    printf("Enter a integer or 'end' to stop: ");
    if (!fgets(string, 32, stdin))
        return input_warning_and_free_memory("The input reading failed (EOF or input error).\n", string);

    string[strcspn(string, "\n")] = '\0';

    if (string[0] == '\0')
        return input_warning_and_free_memory("Empty input.\n", string);

    return string;
}

void update_list_and_array(struct node ***node_array, size_t *count, struct node **head, long val) {
    int value = (int)val;
    nnode **tmp = realloc(*node_array, (*count + 1) * sizeof * node_array);
    *node_array = tmp;
    *head = append_node(*head, value);
    (*node_array)[(*count)++] = *head;
}

struct node *append_node(struct node *head, int value) {
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

char *input_warning_and_free_memory(char *description, char* string) {
    printf("%s", description);
    free(string);
    return NULL;
}