#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

int n;

vector<int> list;

void draw_list() {
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < n; j++) {
            int x = list[j];
            string s = (x <= i) ? "██" : "  ";
            cout << s;
        }
        cout << endl;
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
}
