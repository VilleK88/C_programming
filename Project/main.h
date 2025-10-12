#ifndef MAIN_H
#define MAIN_H

#define ROW_C 26
#define SEAT_C 7
#define INPUT_LENGTH 100
#define BUFFER_SIZE 200
#define LINE_LENGTH 100

typedef struct passenger_ {
    char first_name[100];
    char last_name[100];
    int row_num;
    char row_seat[2];
} passenger;

#endif