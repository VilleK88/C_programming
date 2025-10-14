#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
// & = AND
// | = OR
// ^ = XOR
// << left shift
// >> right shift

bool binary_parser(const char *str, unsigned int *pu);
int digit_counter(unsigned int nr);

int main() {
    char *str = "0b101yogurt";
    unsigned int val = 0;
    if (binary_parser(str, &val)){
        printf("Decimal: %u\nHex: %08X\nHex digits needed: %d", val, val, digit_counter(val));
    }
    else printf("Failed to parse binary\n");

    return 0;
}

bool binary_parser(const char *str, unsigned int *pu) {
    if (str != NULL) {
        const char *p = str;
        while (*p && isspace(*p)) {
            p++;
        }

        const char *prefix = p + 0;

        if (strncmp(prefix, "0b", 2) == 0) {
            p += 2;

            const char *bits = p;
            while (*bits == '0' || *bits == '1') {
                bits++;
            }

            const int bits_len = (int)(bits - p);

            if (bits_len > 0) {
                unsigned int result = 0;
                for (int i = 0; i < bits_len; i++) {
                    const int bit = p[i] - '0';
                    result = result << 1 | (unsigned)bit;
                }

                *pu = result;
                return true;
            }
        }

        return false;
    }

    return false;
}

int digit_counter(unsigned int nr) {
    int d = 0;

    do {
        d++; nr >>= 4;
    } while (nr);

    return d;
}