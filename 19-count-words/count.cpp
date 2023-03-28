#include <iostream>
#include <string>
#include <string_view>

using std::cin;
using std::cout, std::endl;

struct CountableString {
private:
    /** String data representation. */
    std::string data;

    /** View pointing to last read string line. */
    std::string_view current_line;

public:
    /** Appends line to string, bar special character case. */
    CountableString & operator+=(const std::string &line) {
        if (line[0] != '@') {
            data += line;
            current_line = line;
        }
        return *this;
    }

    /** Prints whole string. */
    void print() {
        cout << data << endl;
    }

    /** Prints current string line. */
    void print_line() {
        cout << current_line << endl;
    }
};

int main() {
    CountableString cs;
    std::string aux;
    getline(cin, aux);
    cs += aux;
    cs.print();
    cs.print_line();
}
