#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
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
    char *str = "  0b00000110";
    unsigned int *pu = 0;

    binary_parser(str, pu);

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
            const int len = (int)strlen(p);
            char binary_code[len-1];
            binary_code[len-2] = '\0';

            //printf("p len: %d\n", len);
            for (int i = 2; i < len; i++) {
                if (isdigit(p[i])) {
                    binary_code[i-2] = p[i];
                    //printf("p: %c\n", p[i]);
                }
            }

            int result = 0;
            int potence = 0;
            const int bi_len = (int)strlen(binary_code);
            for (int i = bi_len-1; i >= 0; i--) {
                const int bit = binary_code[i] - '0';
                printf("%d\n", bit);
                result += bit << potence;
                //printf("Result during loop: %d\n", result);
                potence += 1;
            }

            printf("Result: %d\n", result);
        }
    }

    return false;
}

int digit_counter(unsigned int nr) {
    
}