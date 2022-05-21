#include <cstdio>
#include <cstdlib>
#include <vector>

#include "util.h"

using namespace std;

static int m;
static int n;

class Snake {
public:
    /** How big the snake currently is. */
    int size;

    /** Which direction the snake is currently facing. */
    Orientation orientation = RIGHT;

    /** List of positioned pieces the snake is formed of. */
    vector<SnakePiece> pieces;

    /** Creates snake with designated size. */
    Snake(int _size) {
        size = _size;
        int x0 = m/2;
        int y0 = n/2;
        for (int k = 0; k < size; k++) {
            int y = y0 + k;
            char c = (k < size-1) ? '=' : '>';
            SnakePiece piece = {x0, y, c};
            pieces.push_back(piece);
        }
    }

    /** Draws snake pieces, according to their position. */
    void draw() {
        for (auto& piece : pieces) {
            draw_in_position(piece.x, piece.y, piece.type);
        }
    }
};

/** Draws empty snake arena. */
void draw_empty_arena() {
    for (int i = 0; i <= m+1; i++) {
        for (int j = 0; j <= n+1; j++) {
            if (i == 0 or i == m+1 or j == 0 or j == n+1) {
                printf("█");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int main(int argc, char **argv) {
    // Receive arguments
    if (argc < 3) {
        return EXIT_FAILURE;
    }
    m = atoi(argv[1]);
    n = atoi(argv[2]);

    // Print dimensions and draw arena
    system("clear");
    printf("m = %d\n", m);
    printf("n = %d\n\n", n);
    draw_empty_arena();
    printf("\n");

    Snake snake(5);
    snake.draw();
    draw_in_position(m+2, n+1, '\n');
}
