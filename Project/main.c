#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h> // isdigit

#define row_c 26
#define seat_c 6

void initialize_rows(char rows[row_c][seat_c]);
void print_rows(char rows[row_c][seat_c]);
void update_rows(char rows[row_c][seat_c]);
FILE *open_file(char *filename);
int get_nums_from_a_string(const char *string);
int find_seat(const char *string, char c);
int menu();
void input_passenger_info();
bool add_passenger();
char *handle_input(int size);
char *input_warning_free_memory(char *error_msg, char *string);

int main() {
    char rows[row_c][seat_c];
    bool continue_loop = true;
    initialize_rows(rows);
    update_rows(rows);
    //print_rows(rows);

    do {
        //menu();
        printf("1) reserve a seat\n2) seat map\n3) exit\n");
        const char *c = handle_input(3);
        if (c) {
            if (isdigit(*c)) {
                const int choice = atoi(c);
                //printf("You chose: %d\n", choice);
                switch (choice) {
                    case 1:
                        printf("Reserve a seat chosen.\n");
                        break;
                    case 2:
                        printf("Seat map chosen.\n");
                        break;
                    case 3:
                        printf("Exit chosen.\n");
                        continue_loop = false;
                        break;
                    default:
                        printf("Invalid input. Only enter integers (1-3).\n");
                        break;
                }
            }
            else
                printf("Invalid input. Only enter integers (1-3).\n");
        }

    } while (continue_loop);

    return 0;
}

void initialize_rows(char rows[row_c][seat_c]) {
    for (int i = 0; i < row_c; i++) {
        for (int j = 0; j < seat_c; j++) {
            const char seats[seat_c] = {'A', 'B', 'C', 'D', 'E', 'F'};
            rows[i][j] = seats[j];
        }
    }
}

void print_rows(char rows[row_c][seat_c]) {
    for (int i = 0; i < row_c; i++) {
        printf("%2d ", i+1);
        for (int j = 0; j < 3; j++) {
            printf("%c", rows[i][j]);
        }
        printf("   ");
        for (int j = 3; j < seat_c; j++) {
            printf("%c", rows[i][j]);
        }
        printf("\n");
    }
}

void update_rows(char rows[row_c][seat_c]) {
    char line[100];
    FILE *file = open_file("seat_reservations.csv");

    while (fgets(line, sizeof(line), file) != NULL) {
        char *current_line = line;
        int count = 0;

        while (count < 2 && (current_line = strchr(current_line, ',')) != NULL) {
            current_line++;
            count++;
        }

        const int row_num = get_nums_from_a_string(current_line);
        size_t len = strlen(current_line);

        if (len > 0 && current_line[len - 1] == '\n') {
            current_line[len- 1] = '\0';
            len--;
        }

        if (len > 0) {
            const char last = current_line[len - 1];
            if (row_num > 0) {
                const int seat_num = find_seat(rows[row_num], last);
                rows[row_num][seat_num] = 'x';
            }
        }

    }

}

FILE *open_file(char *filename) {
    FILE *file;

    if ((file = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Error: could not open file %s\n", filename);
        free(filename);
        exit(EXIT_FAILURE);
    }

    return file;
}

int get_nums_from_a_string(const char *string) {
    char *num_char = malloc(strlen(string) + 1);

    int j = 0;
    for (int i = 0; string[i] != '\0'; i++) {
        if (isdigit(string[i])) {
            num_char[j++] = string[i];
        }
    }
    num_char[j] = '\0';
    int result = 0;
    if (j > 0) {
        result = atoi(num_char);
    }

    free(num_char);
    return result;
}

int find_seat(const char *string, const char c) {
    if (string != NULL) {
        for (int i = 0; string[i] != '\n'; i++) {
            if (string[i] == c)
                return i;
        }
    }
    return 0;
}

int menu() {
    printf("1) reserve a seat\n2) seat map\nexit\n");
}

void input_passenger_info() {

}

bool add_passenger() {
    return true;
}

char *handle_input(const int size) {
    char *string = malloc(size);

    if (string) {
        if (fgets(string, size, stdin)) {
            if (strchr(string, '\n') == NULL) {
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF){}
                return input_warning_free_memory("Input too long.", string);
            }
            string[strcspn(string, "\n")] = '\0';

            if (string[0] == '\0')
                return input_warning_free_memory("Empty input.", string);
        }
    }
    else
        return input_warning_free_memory("Memory allocation failed.", string);

    return string;
}

char *input_warning_free_memory(char *error_msg, char *string) {
    printf("%s\n", error_msg);
    free(string);
    return NULL;
}