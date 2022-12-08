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

uint64_t get_bit_array(const char *str, int len) {
    uint64_t array = 0;
    for (int i = 0; str[i] && i < len; i++) {
        uint64_t exponent = str[i] < 'a'
            ? str[i] - 'A' + 'z' - 'a' + 1
            : str[i] - 'a';
        printf("%c: %lu - %d\n", str[i], exponent, len);
        array |= powd(2, exponent);
    }
    return array;
}

uint64_t get_elf_priority_value(const char *sack_1, const char *sack_2, int len) {
    uint64_t arr_1 = get_bit_array(sack_1, len);
    uint64_t arr_2 = get_bit_array(sack_2, len);
    uint64_t arr_common = arr_1 & arr_2;
    return get_value(arr_common);
}

uint64_t get_group_priority_value(const char *elf_1, const char *elf_2, const char *elf_3) {
    uint64_t arr_1 = get_bit_array(elf_1, strlen(elf_1) - 1);
    uint64_t arr_2 = get_bit_array(elf_2, strlen(elf_2) - 1);
    uint64_t arr_3 = get_bit_array(elf_3, strlen(elf_3) - 1);
    uint64_t arr_common = arr_1 & arr_2 & arr_3;
    return get_value(arr_common);
}

int main(int argc, char* argv[]) {
    FILE* input = fopen("input.txt", "r");
    if (!input) {
        printf("Holly wacamolly\n");
        return EXIT_FAILURE;
    }

    uint64_t score_1 = 0;
    uint64_t score_2 = 0;

    int elfs = 0;
    char elf_1[100], elf_2[100], elf_3[100];
    char *group[] = { elf_1, elf_2, elf_3 };
    while (fgets(group[elfs], 100, input)) {
        char* elf = group[elfs];
        int sack_len = strlen(elf) / 2;
        score_1 += get_elf_priority_value(elf, elf + sack_len, sack_len);

        if (++elfs == 3) {
            score_2 += get_group_priority_value(group[0], group[1], group[2]);
            elfs = 0;
        }
    }
    fclose(input);

    printf("Total 1: %lu\n", score_1);
    printf("Total 2: %lu\n", score_2);

    return EXIT_SUCCESS;
}
