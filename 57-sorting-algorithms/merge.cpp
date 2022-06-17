#include "sorting.h"

void Merge::sort() {
    inner_sort(0, n-1);
}

/** Performs merge sort on list interval [l, r]. */
void Merge::inner_sort(int l, int r) {
    if (l == r) {
        // Segment of size 1
        return;
    }
    // Split sublist in half and recursively order segments
    int m = (l + r + 1) / 2;
    inner_sort(l, m-1);
    inner_sort(m, r);

    // Build auxiliary list by intercalating terms from both segments
    vector<int> aux;
    aux.reserve(r - l + 1);
    int i = l;
    int j = m;
    while (i <= m-1 or j <= r) {
        if (i > m-1) {
            aux.push_back(list[j++]);
        } else if (j > r) {
            aux.push_back(list[i++]);
        } else {
            int val = (list[i] < list[j]) ? list[i++] : list[j++];
            aux.push_back(val);
        }
    }
    // Insert ordered terms in original list
    for (int i = l; i <= r; i++) {
        list[i] = aux[i - l];
        draw_list();
    }
}
