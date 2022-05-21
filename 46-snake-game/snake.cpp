#include <cstdio>
#include <cstdlib>

using namespace std;

/** Draws empty snake arena. */
void draw_arena(int m, int n) {
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
    int m = atoi(argv[1]);
    int n = atoi(argv[2]);

    // Print dimensions and draw arena
    system("clear");
    printf("m = %d\n", m);
    printf("n = %d\n\n", n);
    draw_arena(m, n);
    printf("\n");
}
