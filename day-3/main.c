#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

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
        array |= 1L << exponent;
    }
    return array;
}

uint64_t get_elf_priority_value(const char* elf) {
    int sack_len = strlen(elf) / 2;
    const char* sack_1 = elf;
    const char* sack_2 = elf + sack_len;
    uint64_t arr_1 = get_bit_array(sack_1, sack_len);
    uint64_t arr_2 = get_bit_array(sack_2, sack_len);
    uint64_t arr_common = arr_1 & arr_2;
    return get_value(arr_common);
}

uint64_t get_group_priority_value(char* elfs[3]) {
    uint64_t arr_1 = get_bit_array(elfs[0], strlen(elfs[0]) - 1);
    uint64_t arr_2 = get_bit_array(elfs[1], strlen(elfs[1]) - 1);
    uint64_t arr_3 = get_bit_array(elfs[2], strlen(elfs[2]) - 1);
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
        score_1 += get_elf_priority_value(group[elfs]);
        elfs++;

        if (elfs == 3) {
            score_2 += get_group_priority_value(group);
            elfs = 0;
        }
    }
    fclose(input);

    printf("Total 1: %lu\n", score_1);
    printf("Total 2: %lu\n", score_2);

    return EXIT_SUCCESS;
}
