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
        if (*p & 0x80) {
            // UTF-8 multi-byte char support
            char *q = p - 1;
            while (! (*q & 0x40)) {
                q--;
            }
            for (char *r = q; r <= p; r++) {
                putchar(*r);
            }
            p = q;
        } else {
            putchar(*p);
        }
    }
    puts("");
}
