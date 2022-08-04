#include <chrono>
#include <iostream>
#include <thread>

#include "sorting.h"

using namespace std;

unique_ptr<Sorting> Sorting::init(
    const vector<int> &list, const string &algorithm
) {
    unique_ptr<Sorting> sorting;
    if (algorithm == "bubble") {
        sorting = make_unique<Bubble>();
    } else if (algorithm == "selection") {
        sorting = make_unique<Selection>();
    } else if (algorithm == "insertion") {
        sorting = make_unique<Insertion>();
    } else if (algorithm == "merge") {
        sorting = make_unique<Merge>();
    } else if (algorithm == "quick") {
        sorting = make_unique<Quick>();
    } else if (algorithm == "heap") {
        sorting = make_unique<Heap>();
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
