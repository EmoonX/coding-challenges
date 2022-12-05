#include <iostream>
#include <string>
#include <vector>

using namespace std;

/** N-dimensional vector. */
class Vector {
private:
    /** Vector name. */
    string name;

    /** Vector's numerical components. */
    vector<double> v;

public:
    /** Builds named vector from input values. */
    Vector(const string &name, const string &input)
        : name(name)
    {
        for (size_t l = 0, r = 0; r <= input.size(); r++) {
            if (input[r] == ' ' or r == input.size()) {
                string s = input.substr(l, r - l);
                double x = stod(s);
                v.push_back(x);
                l = r + 1;
            }
        }
    }
    
    /** Prints vector representation. */
    void print() {
        cout << name << ": ( ";
        for (double x : v) {
            cout << x << " ";
        }
        cout << ")" << endl;
    }
};

/** Reads values from input and returns a Vector. */
Vector read_vector(const string &name) {
    string input;
    getline(cin, input);
    return Vector(name, input);
}

int main() {
    // Something
    Vector u = read_vector("u");
    Vector v = read_vector("v");
    
    // More things
    u.print();
    v.print();
}
