#include <stdio.h>

/** UTF-8 multi-byte char support. */
void process_multibyte(char *p) {
    static char utf8_stack[4];
    static char *q = utf8_stack;
    *q = *p;
    if (*p & 0x40) {
        for (; q >= utf8_stack; q--) {
            putchar(*q);
        }
    }
    q++;
}

int main() {
    size_t SIZE = 1024;
    char s[SIZE], *p;
    for (p = s; p - s < SIZE; p++) {
        *p = getchar();
        if (*p == '\n') {
            break;
        }
    }
    for (p--; p >= s; p--) {
        if (*p & 0x80) {
            process_multibyte(p);
        } else {
            putchar(*p);
        }
    }
    puts("");
}
