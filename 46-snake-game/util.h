#include <cstdio>

/** Cardinal orientations. */
enum Orientation {
    UP, DOWN, LEFT, RIGHT
};

/** A positioned piece of the whole snake. */
struct SnakePiece {
    int x;
    int y;
    char type;
};

/** Draws char in specified position. */
void draw_in_position(int x, int y, char c) {
    printf("\x1b[%d;%dH", x+4, y+1);
    putchar(c);
    printf("\x1b[%d;%dH", x+4, y+1);
}
