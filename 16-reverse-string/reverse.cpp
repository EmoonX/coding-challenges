#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;

int main() {
    string s;
    getline(cin, s);
    for (auto it = s.rbegin(); it != s.rend(); it++) {
        // Won't work really well for multibyte chars
        cout << *it;
    }
    cout << endl;
}
