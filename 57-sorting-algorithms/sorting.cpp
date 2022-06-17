#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <map>
#include <random>
#include <thread>
#include <vector>

using namespace std;

/** How many values in list. */
int n;

/** The list to be sorted. */
vector<int> list;

/**
 * Visually draws list as a graph on screen.
 */
void draw_list() {
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

/**
 * Swaps two values if x > y.
 * Returns whether swap happened or not.
 */
bool check_and_swap(int& x, int& y) {
    if (x > y) {
        int aux = x;
        x = y;
        y = aux;
        return true;
    }
    return false;
}

/**
 * Bubble sort, O(n²).
 *
 * Compares adjacent values and swaps them if out of order,
 * moving the smallest value to the start of the unordered portion.
 */
void bubble_sort() {
    for (int i = 0; i < n-1; i++) {
        for (int j = n-1; j > i; j--) {
            bool change = check_and_swap(list[j-1], list[j]);
            if (change) {
                draw_list();
            }
        }
    }
}

/**
 * Selection sort, O(n²).
 *
 * Compares first unordered element to all the others,
 * moving a smaller one to the start whenever it's found.
 */
void selection_sort() {
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            bool change = check_and_swap(list[i], list[j]);
            if (change) {
                draw_list();
            }
        }
    }
}

int main(int argc, char **argv) {
    // Map of availabe algorithms
    map<string, void (*)()> algorithms = {
        {"bubble", bubble_sort},
        {"selection", selection_sort},
    };
    // Receive arguments
    if (argc != 3 or (not algorithms.count(argv[2]))) {
        fprintf(stderr, "Usage: %s <size> <algorithm>\n\n", argv[0]);
        fputs("• size\n    Size of the list to be sorted.\n\n", stderr);
        fputs("• algorithm\n    Sorting algorithm to be used.\n    ( ", stderr);
        for (auto& algo : algorithms) {
            cerr << "\"" << algo.first << "\" ";
        }
        fprintf(stderr, ")\n\n");
        return EXIT_FAILURE;
    }
    n = atoi(argv[1]);
    string algorithm = argv[2];

    // Build list of consecutive integers
    for (int k = 1; k <= n; k++) {
        list.push_back(k);
    }
    // Shuffle list using random seed
    random_device rd;
    shuffle(list.begin(), list.end(), default_random_engine(rd()));
    draw_list();

    // Get function pointer from string and call it
    auto sort_function = algorithms[algorithm];
    sort_function();
}
