#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN 32

typedef struct student_{ char name[MAX_LEN]; int group; int id; } student;
int move(student *source, int group, student *target, int size);
void print_array(student *array, int size);

int main() {
    student source[] = {
        {"Ian McShane",    1, 2019001},
        {"John Woo",       3, 2019007},
        {"Nick Name",      3, 2019019},
        {"Molly Westwood", 2, 2019021},
        {"Peter Thornton", 2, 2019031},
        {"Sammy Davis",    3, 2019671},
        {"Will Smith",     1, 2019761},
        {"Patti Smith",    4, 2018492},
        {"Willy Wonka",    2, 2016290},
        {"Jack Daniels",   4, 2016892},
        {"Ernie West",     1, 2015192},
        {"Sean Bean",      2, 2016112},
        {"Eric Idle",      2, 2017822},
        {"Susan Sarandon", 5, 2016034},
        {"Nick Cave",      5, 2015002},
        {"", 0, 0}
    };
    int size = 15;
    student target[15];
    target[0].id = 0;

    int moved_elements = move(source, 3, target, size);

    print_array(source, size - moved_elements);
    printf("\nTarget array:\n");
    print_array(target, moved_elements);

    return 0;
}

int move(student *source, int group, student *target, int size) {
    int group_count = 0;
    int index;
    int target_index = 0;

    while (target_index < size && target[target_index].id != 0) {
        target_index++;
    }
    if (target_index >= size - 1)
        return 0;

    int source_index = 0;
    int source_len = 0;
    while (source[source_index].id != 0) {
        source_len++;
        source_index++;
    }
    int new_size = source_len;

    // count how many students are included in the group
    for (int i = 0; i < source_len; i++) {
        if (source[i].group == group) {
            group_count++;
        }
    }

    if (group_count > 0) {
        int moved_items = 0;

        do {

            if (target_index >= size - 1)
                break;

            // find the student index and send the student to the target array
            for (int i = 0; i < new_size; i++) {
                if (source[i].group == group) {
                    index = i;
                    target[target_index++] = source[i];
                    moved_items++;
                    break;
                }
            }

            // move the elements to the left
            while (source[index].id != 0) {
                source[index] = source[index + 1];
                index++;
            }

            group_count--;
            new_size--;
        } while (group_count > 0 && target_index < size - 1);

        target[target_index].id = 0;
        source[new_size].id = 0;

        return moved_items;
    }
    return 0;
}

void print_array(student *array, int size) {
    char *titles[] = {"Name", "Group", "ID"};
    printf("%-20s %-7s %s\n", titles[0], titles[1], titles[2]);

    for (int i = 0; i < size; i++) {
        printf("%-20s %-7d %d\n", array[i].name, array[i].group, array[i].id);
    }
}