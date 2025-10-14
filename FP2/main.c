#include <stdio.h>
#include <string.h>

#define MAX_LEN 32
typedef struct student_ {
    char name[MAX_LEN];
    int group;
    int id;
} student;

typedef enum { byGroup, byLastName, byFirstName } sort_order;

void sort_students(student *students, int count, sort_order sb);
int sort_by_group(const void *a, const void *b);
int sort_by_first_name(const void *a, const void *b);
int sort_by_last_name(const void *a, const void *b);
void print_students(const student *students);

int main() {
    student students[] = {
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

    print_students(students);
    //sort_students(students, 0, byFirstName);
    //sort_students(students, 0, byLastName);
    sort_students(students, 0, byGroup);
    printf("\n");
    print_students(students);

    return 0;
}

/*void sort_students(student *students, int count, sort_order sb) {
    int in_count = 0;
    if (count <= 0) {
        for (int i = 0; students[i].id != 0; i++) {
            in_count ++;
        }
    }
    else
        in_count = count;

    switch (sb+1) {
        case 1:
            qsort(students, in_count, sizeof(student), sort_by_group);
            break;
        case 2:
            qsort(students, in_count, sizeof(student), sort_by_last_name);
            break;
        case 3:
            qsort(students, in_count, sizeof(student), sort_by_first_name);
            break;
        default:
            break;
    }
}*/

int sort_by_group(const void *a, const void *b) {
    const student *sa = a;
    const student *sb = b;
    return sa->group - sb->group;
}

int sort_by_first_name(const void *a, const void *b) {
    return strcmp(((struct student_*)a)->name, ((struct student_*)b)->name);
}

int sort_by_last_name(const void *a, const void *b) {
    const student *sa = a;
    const student *sb = b;
    const char *last_a = strrchr(sa->name, ' ');
    const char *last_b = strrchr(sb->name, ' ');

    last_a = last_a ? last_a + 1 : sa->name;
    last_b = last_b ? last_b + 1 : sb->name;

    return strcmp(last_a, last_b);
}

void print_students(const student *students) {
    char *titles[] = {"Name", "Group", "ID"};
    printf("%-15s %-15s %s\n", titles[0], titles[1], titles[2]);

    for (int i = 0; students[i].id != 0; i++) {
        student item = students[i];
        printf("%-15s %-15d %d\n", item.name, item.group, item.id);
    }
}

void sort_students(student *students, int count, sort_order sb) {
    if (count <= 0) {
        count = 0;
        while (students[count].id != 0) {
            count++;
        }

        
        for (int i = 0; i < count - 1; ++i) {
            int min = i;
            for (int j = i + 1; j < count; ++j) {
                int take = 0;

                switch (sb) {
                    case byGroup:
                        take = students[j].group < students[min].group;
                        break;

                    case byFirstName:
                        take = strcmp(students[j].name, students[min].name) < 0;
                        break;

                    case byLastName: {
                        const char *aj = strrchr(students[j].name, ' ');
                        const char *am = strrchr(students[min].name, ' ');
                        aj = aj ? aj + 1 : students[j].name;
                        am = am ? am + 1 : students[min].name;
                        take = strcmp(aj, am) < 0;
                        break;
                    }

                    default:
                        break;
                }

                if (take)
                    min = j;
            }

            if (sb == byGroup) {
                student key = students[min];
                for (int k = min; k > i; --k)
                    students[k] = students[k - 1];
                students[i] = key;
            } else {
                student tmp = students[i];
                students[i] = students[min];
                students[min] = tmp;
            }
        }

    }
    else {
        for (int i = 0; i < count - 1; ++i) {
            int min = i;
            for (int j = i + 1; j < count; ++j) {
                int take = 0;

                switch (sb) {
                    case byGroup:
                        take = students[j].group < students[min].group;
                        break;

                    case byFirstName:
                        take = strcmp(students[j].name, students[min].name) < 0;
                        break;

                    case byLastName: {
                        const char *aj = strrchr(students[j].name, ' ');
                        const char *am = strrchr(students[min].name, ' ');
                        aj = aj ? aj + 1 : students[j].name;
                        am = am ? am + 1 : students[min].name;
                        take = strcmp(aj, am) < 0;
                        break;
                    }

                    default:
                        break;
                }

                if (take)
                    min = j;
            }

            if (min != i) {
                student tmp = students[i];
                students[i] = students[min];
                students[min] = tmp;
            }
        }
    }
}
