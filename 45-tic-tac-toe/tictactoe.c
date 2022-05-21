#include <stdio.h>

static int n = 3;

/**
 * Draws tic-tac-toe grid on screen.
 */
void draw_grid() {
    system("clear");
    for (int i = 0; i < n; i++) {
        for (int k = 1; k <= 3; k++) {
            for (int j = 0; j < n; j++) {
                if (k < 3) {
                    printf("   %s", (j < n-1) ? "|" : "");
                } else if (i < n-1) {
                    printf("---%s", (j < n-1) ? "+" : "");
                }
            }
            puts("");
        }
    }
}

int main() {
    draw_grid();
}
