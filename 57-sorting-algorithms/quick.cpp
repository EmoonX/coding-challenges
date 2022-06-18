#include <utility>

#include "sorting.h"

using std::swap;

void Quick::sort() {
    inner_sort(0, n-1);
}

/** Performs quicksort on list interval [l, r]. */
void Quick::inner_sort(int l, int r) {
    if (r - l <= 1) {
        // Segment of size <= 2
        if (r == l+1 and list[l] > list[r]) {
            swap(list[l], list[r]);
            draw_list();
        }
        return;
    }
    // Randomly pick pivot in interval
    int p = l + (rand() % (r - l + 1));
    swap(list[p], list[r]);
    draw_list();

    // Move terms smaller than pivot to the left
    int i = l;
    for (int j = l; j <= r; j++) {
        if (list[j] < list[r]) {
            if (i < j) {
                swap(list[i], list[j]);
                draw_list();
            }
            i++;
        }
    }
    // Put pivot in the correct position
    if (i < r) {
        swap(list[i], list[r]);
        draw_list();
    }
    // Recursively order segments to the left & right of pivot
    inner_sort(l, i-1);
    inner_sort(i, r);
}
