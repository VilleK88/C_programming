#include <stdio.h>

#define MAX_LEN 32

typedef struct student_{ char name[MAX_LEN]; int group; int id; } student;
int move(student *source, int group, student *target, int size);
void print_array(student *array);

int main() {
    student source[] = {
        {"Ian McShane",    1, 2019001},
        {"John Woo",       3, 2019007},
        {"Nick Cave",      3, 2019019},
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
    //int size = 15;
    student target[13];
    target[0].id = 0;
    int target_size = 13;

    printf("Initial array:\n");
    print_array(source);

    int moved_elements = move(source, 3, target, target_size);
    printf("\n\nMoved %d elements\n\n", moved_elements);
    print_array(source);
    printf("\ntarget array:\n");
    print_array(target);

    moved_elements = move(source, 5, target, target_size);
    printf("\n\nMoved %d elements\n\n", moved_elements);
    print_array(source);
    printf("\ntarget array:\n");
    print_array(target);

    moved_elements = move(source, 2, target, target_size);
    printf("\n\nMoved %d elements\n\n", moved_elements);
    print_array(source);
    printf("\ntarget array:\n");
    print_array(target);

    moved_elements = move(source, 1, target, target_size);
    printf("\n\nMoved %d elements\n\n", moved_elements);
    print_array(source);
    printf("\ntarget array:\n");
    print_array(target);

    moved_elements = move(source, 4, target, target_size);
    printf("\n\nMoved %d elements\n\n", moved_elements);
    print_array(source);
    printf("\ntarget array:\n");
    print_array(target);

    return 0;
}

int move(student *source, int group, student *target, int size) {
    int group_count = 0;
    int index = 0;
    int target_index = 0;

    while (target_index < size && target[target_index].id != 0) {
        target_index++;
    }

    int source_index = 0;
    int source_len = 0;
    while (source[source_index].id != 0) {
        source_len++;
        source_index++;
    }

    // count how many students are included in the group
    for (int i = 0; i < source_len; i++) {
        if (source[i].group == group) {
            group_count++;
        }
    }

    if (group_count + target_index >= size - 1)
        return 0;

    int moved_items = 0;

    do {
        // find the student index and send the student to the target array
        for (int i = 0; i < source_len; i++) {
            if (source[i].group == group && target_index < size - 1) {
                index = i;
                target[target_index++] = source[i];
                moved_items++;
                break;
            }
        }

        // move the elements to the left
        while (source[index].id != 0 && target_index < size - 1) {
            source[index] = source[index + 1];
            index++;
        }

        group_count--;
        source_len--;
    } while (group_count > 0 && target_index < size - 1);

    target[target_index].id = 0;
    source[source_len].id = 0;

    if (target_index <= size - 1)
        return moved_items;

    return 0;
}

void print_array(student *array) {
    char *titles[] = {"Name", "Group", "ID"};
    printf("%-20s %-7s %s\n", titles[0], titles[1], titles[2]);

    for (int i = 0; array[i].id != 0; i++) {
        printf("%-20s %-7d %d\n", array[i].name, array[i].group, array[i].id);
    }
}