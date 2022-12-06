#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

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
    double dot(const Vector &v) const {
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
        const Vector &u = *this;
        string name = u.name + " x " + v.name;
        Vector w(name, "0 0 0");
        static vector<size_t> perm = {0, 1, 2};
        do {            
            int inversion_count = 0;
            for (size_t k = 1; k <= 3; k++) {
                if (perm[k-1] >= k) {
                    inversion_count++;
                }
            }
            int factor = (inversion_count % 2 == 0) ? 1 : -1;
            w[perm[0]] = factor * u[perm[1]] * v[perm[2]];
        } while (next_permutation(perm.begin(), perm.end()));
        return w;
    }
    
    /** Prints vector representation. */
    void print() const {
        printf("%s = [ ", name.c_str());
        for (double x : vec) {
            printf("%g ", x);
        }
        puts("]");
    }
};

/** Reads values from input and returns a Vector. */
Vector read_vector(const string &name) {
    string input;
    getline(std::cin, input);
    return Vector(name, input);
}

int main() {
    // Receive inputs
    Vector u = read_vector("u");
    Vector v = read_vector("v");

    // Calculate and print results
    double dot = u.dot(v);
    Vector cross = u.cross(v);
    u.print();
    v.print();
    printf("u . v = %g\n", dot);
    cross.print();
}
