#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 32

typedef struct student_ {
    char name[MAX_LEN];
    int group;
    int id;
    struct student_ *next;
} student;

int move(student **source, int group, student **target);
void print_linked_list(const student *list);

int main() {
    student n6 = { "Frank", 1, 106, NULL };
    student n5 = { "Eve",   2, 105, &n6 };
    student n4 = { "David", 3, 104, &n5 };
    student n3 = { "Carol", 1, 103, &n4 };
    student n2 = { "Bob",   2, 102, &n3 };
    student n1 = { "Alice", 1, 101, &n2 };
    student *source = &n1;   /* head */
    student *target = NULL;

    int moved = move(&source, 1, &target);
    print_linked_list(source);
    printf("\n\n");
    print_linked_list(target);

    return 0;
}

int move(student **source, int group, student **target) {
    int moved = 0;

    for (student **pp = source; *pp != NULL;) {
        student *s_item = *pp;
        if (s_item->group == group) {
            *pp = s_item->next;
            s_item->next = *target;
            *target = s_item;
            moved++;
        }
        else {
            pp = &s_item->next;
        }
    }

    return moved;
}

void print_linked_list(const student *list) {
    for (const student *p = list; p; p = p->next) {
        printf("%-15s %-7d %d\n", p->name, p->group, p->id);
    }
}