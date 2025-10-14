#include <stdio.h>
#include <stdint.h>

uint32_t get_bits(uint32_t value, uint32_t shift, uint32_t bits);

int main() {
    printf("get_bits(1, 0, 1)  = %u\n", get_bits(1u, 0u, 1u));      // 1
    printf("get_bits(15, 1, 4) = %u\n", get_bits(15u, 1u, 4u));     // 7

    return 0;
}

uint32_t get_bits(const uint32_t value, const uint32_t shift, const uint32_t bits) {
    const uint32_t shifted = shift >= 32 ? 0u : value >> shift;
    const uint32_t mask = bits >= 32 ? 0xFFFFFFFFu : bits == 0 ? 0u : (1u << bits) - 1u;
    return shifted & mask;
}