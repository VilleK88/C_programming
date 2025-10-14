#include <stdio.h> // printf, fgets, scanf
#include <stdlib.h> // malloc, realloc, free, atoi
#include <string.h> // strlen, strcmp
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_LEN 32
typedef struct student_ {
    char name[MAX_LEN];
    int group;
    int id;
} student;

typedef enum { byGroup, byLastName, byFirstName } sort_order;

void sort_students(student *students, int count, sort_order sb);

int main() {
    return 0;
}

void sort_students(student *students, int count, sort_order sb) {
    
}