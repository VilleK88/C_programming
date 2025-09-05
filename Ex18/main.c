#include <stdio.h>
#include <stdlib.h>

int handle_input();
int generate_random(int value);
void print_hexadecimal(int num, int rand_num);

int main() {
    int num;

    do {
        num = handle_input();
        if (num >= 0 && num <= 15) {
            const int rand_num = generate_random(num);
            print_hexadecimal(num, rand_num);
        }
        else if (num > 15)
            printf("Number is out of range.\n");
    } while (num > -1);

    return 0;
}

int handle_input() {
    int value;
    printf("Enter a number: ");
    if (scanf_s("%d", &value) != 1) {
        while (getchar() != '\n'){}
        printf("Invalid input.\n");
    }
    return value;
}

int generate_random(const int value) {
    int random = value;
    random = rand() % 100;
    return random;
}

void print_hexadecimal(const int num, const int rand_num) {
    const unsigned int shift_right = rand_num  >> num;
    const unsigned int bits = shift_right & 0x3f;
    printf("Random number hexadecimal: %02x\n", bits);
}