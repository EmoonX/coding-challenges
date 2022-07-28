#include <stdbool.h>
#include <stdio.h>

int main() {
    size_t SIZE = 1024;
    char s[SIZE];
    char *p;
    for (p = s; p - s < SIZE; p++) {
        *p = getchar();
        if (*p == '\n') {
            break;
        }
    }
    for (p--; p >= s; p--) {
        putchar(*p);
    }
    puts("");
}
