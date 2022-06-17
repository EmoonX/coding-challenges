#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
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
    n = atoi(argv[1]);

    for (int k = 1; k <= n; k++) {
        list.push_back(k);
    }
    random_device rd;
    shuffle(list.begin(), list.end(), default_random_engine(rd()));
    draw_list();
    // bubble_sort();
    selection_sort();
}
