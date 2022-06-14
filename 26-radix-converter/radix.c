#include <stdio.h>
#include <stdlib.h>

/** Shows program usage and exits. */
void show_usage(char *program_name) {
    printf("Usage: %s <number> <base_from> <base_to>\n\n", program_name);
    puts("• number\n    An integer or floating point number.");
    puts("• base_from, base_to\n    Integer bases from 2 to 36.");
    puts("");
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
    if (argc != 4) {
        show_usage(argv[0]);
    }
    double x = atof(argv[1]);
    int base_from = atoi(argv[2]);
    int base_to = atoi(argv[3]);

    printf("%g (%d) = XXX (%d)\n", x, base_from, base_to);
}
