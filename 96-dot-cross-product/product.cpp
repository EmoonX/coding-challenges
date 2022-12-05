#include <algorithm>
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

    /** Returns `i`-th vector component. */
    double operator[](size_t i) const {
        return vec.at(i);
    }
    /** Returns `i`-th vector component reference (for lvalue usage). */
    double & operator[](size_t i) {
        return vec.at(i);
    }

    /** Calculates dot product between two vectors. Returns a scalar. */
    constexpr double dot(const Vector &v) const {
        const Vector &u = *this;
        double z = 0.0;
        for (size_t i = 0; i < n; i++) {
            z += u[i] * v[i];
        }
        return z;
    }

    /** Calculates cross product between two vectors. 
        Returns a 3-dimensional vector. */
    Vector cross(const Vector &v) const {
        static vector<size_t> perm = {0, 1, 2};
        const Vector &u = *this;
        string name = u.name + " x " + v.name;
        Vector w(name, "0 0 0");
        do {            
            int inversion_count = 0;
            for (size_t k = 1; k <= 3; k++) {
                if (perm[k-1] >= k) {
                    inversion_count++;
                }
            }
            int factor = (inversion_count % 2 == 0) ? 1 : -1;
            w[perm[0]] = factor * u[perm[1]] + v[perm[2]];
        } while (next_permutation(perm.begin(), perm.end()));
        return w;
    }
    
    /** Prints vector representation. */
    void print() const {
        cout << name << " = [ ";
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
    
    // Calculate and print results
    u.print();
    v.print();
    cout << "u . v = " << u.dot(v) << endl;
    (u.cross(v)).print();
}
