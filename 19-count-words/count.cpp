#include <iostream>
#include <string>
#include <string_view>

using std::cin;
using std::cout, std::endl;

struct CountableString {
private:
    /** String's content. */
    std::string data;

    /** View pointing to last read string line. */
    std::string_view current_line;

    /** Token counters. */
    struct {
        uint words;
    } count;

public:
    /** Appends line to string, bar special character case. */
    CountableString & operator+=(const std::string &line) {
        if (line[0] == '@') {
            show_count();
        } else {
            data += line;
            current_line = line;
            update_count();
        }
        return *this;
    }

    /** Update counters. */
    void update_count() {
        bool in_word = false;
        for (auto &c : current_line) {
            if (isgraph(c)) {
                if (not in_word) {
                    in_word = true;
                    count.words++;
                }
            } else {
                in_word = false;
            }
        }
    }

    /** Prints whole string. */
    void print() const {
        cout << data << endl;
    }

    /** Prints string's current line. */
    void print_line() const {
        cout << current_line << endl;
    }

    void show_count() const {
        cout << "> Words: " << count.words << endl;
    }
};

int main() {
    CountableString cs;
    std::string aux;
    getline(cin, aux);
    cs += aux;
    cs.print();
    cs.show_count();
}
