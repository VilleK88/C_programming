#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INPUT_LENGTH 34

typedef struct node {
    int number;
    struct node *next;
} nnode;

char *handle_input(int length);
bool get_input(char *user_input, int length);
void update_list_and_array(struct node ***node_array, size_t *count, struct node **head, long val);
struct node *append_node(struct node *head, int value);
void print_numbers(struct node *head);

int main() {
    nnode **node_array = NULL;
    size_t count = 0;
    struct node *head = NULL;
    bool check = true;

    do {
        char *input = handle_input(INPUT_LENGTH);
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
        free(input);
    } while (check == true);

    print_numbers(head);
    free(node_array);
    return 0;
}

char *handle_input(const int length) {
    char *string = malloc(length);
    if (string) {
        bool stop_loop = false;
        while (!stop_loop) {
            printf("Enter integer: ");
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
        user_input[strcspn(user_input, "\n")] = '\0';
        if (user_input[0] == '\0') {
            printf("Empty input.\n");
            return false;
        }
        return true;
    }
    return false;
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