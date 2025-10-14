#include <stdio.h>
#include <stdint.h>

void print_binaryw(uint32_t value, uint32_t width);

int main() {
    print_binaryw(2, 1);
    printf("\n");
    print_binaryw(1, 8);
    printf("\n");
    print_binaryw(2019, 12);
    printf("\n");

    return 0;
}

void print_binaryw(uint32_t value, uint32_t width) {
    uint32_t needed = 1u;
    for (uint32_t t = value; t >>= 1;) {
        needed++;
    }
    uint32_t n = width > needed ? width : needed;

    for (int i = (int)n - 1; i >= 0; i--) {
        putchar(value >> i & 1u ? '1' : '0');
    }
}