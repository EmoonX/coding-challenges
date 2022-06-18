#include <chrono>
#include <iostream>
#include <thread>

#include "sorting.h"

using namespace std;

Sorting * Sorting::init(const vector<int> &list, const string &algorithm) {
    Sorting *sorting;
    if (algorithm == "bubble") {
        sorting = new Bubble;
    } else if (algorithm == "selection") {
        sorting = new Selection;
    } else if (algorithm == "insertion") {
        sorting = new Insertion;
    } else if (algorithm == "merge") {
        sorting = new Merge;
    } else if (algorithm == "quick") {
        sorting = new Quick;
    } else if (algorithm == "heap") {
        sorting = new Heap;
    } else {
        show_usage_and_exit();
    }
    sorting->list = list;
    sorting->n = list.size();
    return sorting;
}

void Sorting::draw_list() const {
    system("clear");
    for (int i = n; i >= 1; i--) {
        for (int j = 0; j < n; j++) {
            int x = list[j];
            string s = (x >= i) ? "██" : "  ";
            cout << s;
        }
        cout << endl;
    }
    this_thread::sleep_for(chrono::milliseconds(20));
}
