#include <iostream>
#include <string>
#include <vector>

using namespace std;

/** `n`-dimensional vector. */
class Vector {
private:
    /** Vector's name. */
    const string name;

    /** Vector's numerical components. */
    vector<double> vec;

    /** Vector's dimension (i.e number of components) */
    size_t n;

public:
    /** Builds named vector from input values. */
    Vector(const string &name, const string &input)
        : name(name)
    {
        for (size_t l = 0, r = 0; r <= input.size(); r++) {
            if (input[r] == ' ' or r == input.size()) {
                string s = input.substr(l, r - l);
                double x = stod(s);
                vec.push_back(x);
                l = r + 1;
            }
        }
        n = vec.size();
    }

    /** Gets `i`-th vector component. */
    double operator[](size_t i) const {
        return vec.at(i);
    }

    /** Calculates dot product with another vector. */
    double dot(const Vector &v) const {
        const Vector &u = *this;
        double ans = 0.0;
        for (size_t i = 0; i < n; i++) {
            ans += u[i] * v[i];
        }
        return ans;
    }
    
    /** Prints vector representation. */
    void print() const {
        cout << name << ": [ ";
        for (double x : vec) {
            cout << x << " ";
        }
        cout << "]" << endl;
    }
};

/** Reads values from input and returns a Vector. */
Vector read_vector(const string &name) {
    string input;
    getline(cin, input);
    return Vector(name, input);
}

int main() {
    // Receive inputs
    Vector u = read_vector("u");
    Vector v = read_vector("v");
    
    // Print results
    u.print();
    v.print();
    cout << "u . v = " << u.dot(v) << endl;
}
