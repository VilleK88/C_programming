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
void remove_newline(char *user_input);
struct node *add(struct node *head, struct node *item, int value);
void print_numbers(struct node *head);
void free_linked_list(struct node *head);

int main() {
    struct node *head = NULL;
    bool check = true;

    do {
        char *input = handle_input(INPUT_LENGTH);
        char *parse_end;
        // Muuntaa input-merkkijonon long-luvuksi (desimaalina) ja tallentaa osoittimen siihen kohtaan,
        // mihin asti luvun lukeminen onnistui (parse_end osoittaa siihen merkkiin).
        const long val = strtol(input, &parse_end, 10);
        if (*parse_end == '\0') {
            nnode *item = malloc(sizeof(*item));
            if (item) {
                head = add(head, item, (int)val);
            }
            else {
                printf("Memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }
        }
        else if(strcmp(input, "end") == 0) {
            check = false;
        }
        else {
            printf("Invalid input.\n");
        }
        free(input);
    } while (check == true);

    print_numbers(head);
    free_linked_list(head);
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

struct node *add(struct node *head, struct node *item, const int value) {
    item->number = value;
    item->next = NULL;
    if (head == NULL) {
        head = item;
    }
    else {
        struct node *this = head;
        while (this->next != NULL) {
            this = this->next;
        }
        this->next = item;
    }

    return head;
}

void print_numbers(struct node *head) {
    printf("Numbers:\n");
    for (nnode *p = head; p; p = p->next) {
        printf("%d ", p->number);
    }
}

void free_linked_list(struct node *head) {
    while (head) {
        nnode *next = head->next;
        free(head);
        head = next;
    }
}