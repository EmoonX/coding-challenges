#include <iostream>
#include <string>
#include <string_view>

using std::cin;
using std::cout, std::endl;

struct CountableString
{
    std::string data;
    std::string_view line;

    CountableString & operator+=(const std::string &aux) {
        if (aux[0] != '@') {
            data += aux;
            line = aux;
        }
        return *this;
    }

    void print_line() {
        cout << line << endl;
    }
};


int main()
{
    CountableString cs;
    std::string aux;
    getline(cin, aux);
    cs += aux;
    cs.print_line();
}
