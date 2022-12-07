#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

uint64_t powd(uint64_t base, uint64_t exponent) {
    uint64_t result = 1;
    while (exponent--) {
        result *= base;
    }
    return result;
}

uint64_t get_value(uint64_t bit_array) {
    uint64_t value = 0;
    for (int i = 1; bit_array; i++) {
        if (bit_array % 2 == 1) {
            value += i;
        }
        bit_array >>= 1;
    }
    return value;
}

uint64_t get_bit_array(const char *sack, int len) {
    uint64_t array = 0;
    for (int i = 0; i < len; i++) {
        uint64_t exponent = sack[i] < 'a'
            ? sack[i] - 'A' + 'z' - 'a' + 1
            : sack[i] - 'a';
        array |= powd(2, exponent);
    }
    return array;
}

uint64_t get_priority_value(const char *sack_1, const char *sack_2, int len) {
    uint64_t arr_1 = get_bit_array(sack_1, len);
    uint64_t arr_2 = get_bit_array(sack_2, len);
    uint64_t arr_common = arr_1 & arr_2;
    return get_value(arr_common);
}

int main(int argc, char* argv[]) {
    FILE* input = fopen("input.txt", "r");
    if (!input) {
        printf("Holly wacamolly\n");
        return EXIT_FAILURE;
    }

    uint64_t score = 0;
    char line[100];
    while (fgets(line, 100, input)) {
        int sack_len = strlen(line) / 2;
        score += get_priority_value(line, line + sack_len, sack_len);
    }
    fclose(input);

    printf("Total: %lu\n", score);

    return EXIT_SUCCESS;
}
