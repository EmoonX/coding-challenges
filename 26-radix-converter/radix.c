#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** All 36 available digits. */
const char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";

/**
 * Show program usage.
 */
void show_usage(char program_name[]) {
    printf("Usage: %s <number> <base_from> <base_to>\n\n", program_name);
    puts("• number\n    An integer number.");
    puts("• base_from, base_to\n    Integer bases from 2 to 36.");
    puts("");
}

/**
 * Convert string from given base/radix to equivalent one
 * in another base.
 */
void convert(const char input[], char output[], int base_from, int base_to) {
    const char *x = input;
    char *y = output;
    if (input[0] == '-') {
        // Easy hack for negative numbers
        output[0] = '-';
        x++;
        y++;
    }
    // Get base 10 number from input
    long long decimal = 0;
    for (int i = 0; x[i] != '\0'; i++) {
        int k = strchr(digits, x[i]) - digits;
        decimal = (decimal * base_from) + k;
    }
    // Build string in output's base and reverse it
    char aux[128];
    int i;
    for (i = 0; decimal > 0; i++) {
        int k = decimal % base_to;
        char c = digits[k];
        aux[i] = c;
        decimal /= base_to;
    }
    size_t n = i;
    y[i] = '\0';
    for (i--; i >= 0; i--) {
        int j = n - i - 1;
        y[j] = aux[i];
    }
}

int main(int argc, char **argv) {
    // Get arguments
    if (argc != 4) {
        show_usage(argv[0]);
        return EXIT_FAILURE;
    }
    char *input = argv[1];
    int base_from = atoi(argv[2]);
    int base_to = atoi(argv[3]);

    // Convert number and print result
    char output[128];
    convert(input, output, base_from, base_to);
    printf("%s (%d) = %s (%d)\n", input, base_from, output, base_to);
}
