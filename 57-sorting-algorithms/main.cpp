#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <random>
#include <vector>

#include "sorting.h"
#include "util.h"

using namespace std;

int main(int argc, char **argv) {
    // Receive arguments
    if (argc != 3) {
        show_usage_and_exit();
    }
    int n = atoi(argv[1]);
    string algorithm = argv[2];

    // Build list of consecutive integers
    vector<int> list;
    for (int k = 1; k <= n; k++) {
        list.push_back(k);
    }
    // Shuffle list using random seed
    random_device rd;
    shuffle(list.begin(), list.end(), default_random_engine(rd()));

    // Initialize sorting object and sort list
    Sorting *sorting = Sorting::init(list, algorithm);
    sorting->draw_list();
    sorting->sort();
    delete sorting;
    puts("");
}
