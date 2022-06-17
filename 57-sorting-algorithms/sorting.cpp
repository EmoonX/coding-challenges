#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <map>
#include <random>
#include <thread>
#include <vector>

using namespace std;

int n;

vector<int> list;

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

bool check_and_swap(int& x, int& y) {
    if (x > y) {
        int aux = x;
        x = y;
        y = aux;
        return true;
    }
    return false;
}

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
    // Receive arguments
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
    map<string, void (*)()> algorithms = {
        {"bubble", bubble_sort},
        {"selection", selection_sort},
    };
    if (algorithms.count(algorithm)) {
        auto sort_function = algorithms[algorithm];
        sort_function();
    }
}
