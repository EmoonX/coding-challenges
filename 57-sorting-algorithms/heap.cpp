#include <utility>
#include <cstdlib>

#include "sorting.h"

using std::swap;

void Heap::sort() {
    // Build max heap from list values
    for (int i = 0; i < n; i++) {
        int q = i+1;
        while (q > 1) {
            int p = q / 2;
            if (list[p-1] < list[q-1]) {
                swap(list[p-1], list[q-1]);
                draw_list();
            }
            q = p;
        }
    }
    // Get sorted list by moving largest heap elements to the end
    for (int i = n-1; i >= 0; i--) {
        swap(list[0], list[i]);
        draw_list();
        int p = 1;
        while (2*p <= i) {
            // Reestablish heap integrity
            int q1 = 2*p;
            int q2 = 2*p + 1;
            int q = (q1 == i or list[q1-1] > list[q2-1]) ? q1 : q2;
            if (list[p-1] > list[q-1]) {
                break;
            }
            swap(list[p-1], list[q-1]);
            draw_list();
            p = q;
        }
    }
}
