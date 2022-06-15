#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** All 36 available digits. */
const char *digits = "0123456789abcdefghijklmnopqrstuvwxyz";

/**
 * Shows program usage.
 */
void show_usage(char *program_name) {
    printf("Usage: %s <number> <base_from> <base_to>\n\n", program_name);
    puts("• number\n    An integer or floating point number.");
    puts("• base_from, base_to\n    Integer bases from 2 to 36.");
    puts("");
}

/**
 * Converts string from given base/radix to equivalent one
 * in another base.
 */
void convert(char *x, char *y, int base_from, int base_to) {
    long long integer = 0;
    for (int i = 0; x[i] != '\0'; i++) {
        int k = strchr(digits, x[i]) - digits;
        integer = (integer * base_from) + k;
    }
    int i;
    char aux[128];
    for (i = 0; integer > 0; i++) {
        int k = integer % base_to;
        char c = digits[k];
        aux[i] = c;
        integer /= base_to;
    }
    int n = i;
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
    char *x = argv[1];
    int base_from = atoi(argv[2]);
    int base_to = atoi(argv[3]);

    // Convert number and print result
    char y[128];
    convert(x, y, base_from, base_to);
    printf("%s (%d) = %s (%d)\n", x, base_from, y, base_to);
}
