#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define row_c 26
#define seat_c 6

void initialize_rows(char rows[row_c][seat_c]);
void print_rows(char rows[row_c][seat_c]);
void update_rows(char rows[row_c][seat_c]);
FILE *open_file(char *filename, const char *state);
int get_nums_from_a_string(const char *string);
int find_seat(const char *string, char c);
void reserve_a_seat(char rows[row_c][seat_c]);
void add_passenger(const char *first_name, const char *last_name, int row, char seat);
bool needs_line_break();
void show_passengers();
char *handle_input(int length, char *text);
bool get_input(char *user_input, int length);


int main() {
    char rows[row_c][seat_c];
    bool continue_loop = true;
    initialize_rows(rows);
    update_rows(rows);

    do {
        char *c_str = handle_input(3, "1) reserve a seat\n2) seat map\n3) show passengers\n4) exit\n");
        if (isdigit(*c_str)) {
            const int choice = atoi(c_str);
            switch (choice) {
                case 1:
                    reserve_a_seat(rows);
                    break;
                case 2:
                    update_rows(rows);
                    print_rows(rows);
                    break;
                case 3:
                    show_passengers();
                    break;
                case 4:
                    continue_loop = false;
                    break;
                default:
                    printf("Invalid input. Only enter integers (1-3).\n");
                    break;
            }
        }
        else
            printf("Invalid input. Only enter integers (1-3).\n");

        free(c_str);
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
    FILE *file = open_file("seat_reservations.csv", "r");

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
                rows[row_num-1][seat_num] = 'x';
            }
        }
    }
    fclose(file);
}

FILE *open_file(char *filename, const char *state) {
    FILE *file;
    if ((file = fopen(filename, state)) == NULL) {
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

void reserve_a_seat(char rows[row_c][seat_c]) {
    bool continue_loop = true;

    do {
        const char *first_name = handle_input(32, "Enter first name: ");
        const char *last_name = handle_input(32, "Enter last name: ");

        print_rows(rows);

        char *row_str = handle_input(3, "Enter a row number: ");
        if (isdigit(*row_str)) {
            const int row_num = atoi(row_str);
            const char *seat_str = handle_input(3, "Enter a seat (A-F): ");
            const int seat_int = toupper(*seat_str) - 'A';
            if (rows[row_num-1][seat_int] != 'x') {
                add_passenger(first_name, last_name, row_num, *seat_str);
                continue_loop = false;
            }
            else {
                printf("Seat already taken.\n");
                continue_loop = false;
            }
            free(row_str);
        }

    } while (continue_loop);
}


void add_passenger(const char *first_name, const char *last_name, const int row, const char seat) {
    FILE *file = fopen("seat_reservations.csv", "a");

    if (needs_line_break()) {
        fputc('\n', file);
    }

    fprintf(file, "%s,%s,%d,%c", first_name, last_name, row, toupper(seat));
    fclose(file);
    printf("Passenger added\n");
}

bool needs_line_break() {
    FILE *file = open_file("seat_reservations.csv", "rb"); // open file in binary mode
    // check if the file is empty
    const bool empty_file = fseek(file, 0, SEEK_END) == 0 &&  ftell(file) == 0;
    if (!empty_file) {
        const int line_feed = '\x0A'; // represents '\n'
        // determine if a newline character is present if file is not empty
        const bool result = fseek(file, -1, SEEK_END) == 0 && fgetc(file) == line_feed;
        if (!result) {
            fclose(file);
            return true;
        }
    }
    fclose(file);
    return false;
}

void show_passengers() {
    char buffer[200];
    FILE *file = open_file("seat_reservations.csv", "r");

    while (fgets(buffer, sizeof(buffer), file)) {
        char *token = strtok(buffer, ",");
        while (token) {
            printf("%-20s", token);
            token = strtok(NULL, ",");
        }
        printf("\n");
    }

    fclose(file);
}

char *handle_input(const int length, char *text) {
    char *string = malloc(length);
    if (string) {
        bool stop_loop = false;
        while (!stop_loop) {
            printf("%s\n", text);
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