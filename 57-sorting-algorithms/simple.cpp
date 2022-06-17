#include "sorting.h"

void Bubble::sort() {
    for (int i = 0; i < n-1; i++) {
        for (int j = n-1; j > i; j--) {
            bool change = check_and_swap(list[j-1], list[j]);
            if (change) {
                draw_list();
            }
        }
    }
}

void Selection::sort() {
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            bool change = check_and_swap(list[i], list[j]);
            if (change) {
                draw_list();
            }
        }
    }
}

void Insertion::sort() {
    for (int i = 1; i < n; i++) {
        for (int j = i; j >= 0; j--) {
            bool change = check_and_swap(list[j-1], list[j]);
            if (change) {
                draw_list();
            } else break;
        }
    }
}
