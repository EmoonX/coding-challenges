#include <iostream>
#include <string>
#include <utility>

#include "util.h"

using std::cerr, std::string, std::swap;

void show_usage_and_exit() {
    static string algorithms[] = {
        "bubble", "selection", "insertion", "merge", "quick", "heap"
    };
    fputs("Usage: ./a.out <size> <algorithm>\n", stderr);
    fputs("• size\n    Size of the list to be sorted.\n\n", stderr);
    fputs("• algorithm\n    Sorting algorithm to be used.\n    ( ", stderr);
    for (auto &algo : algorithms) {
        cerr << "\"" << algo << "\" ";
    }
    fprintf(stderr, ")\n\n");
    exit(EXIT_FAILURE);
}

bool check_and_swap(int &x, int &y) {
    if (x > y) {
        swap(x, y);
        return true;
    }
    return false;
}
