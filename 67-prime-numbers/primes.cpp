#include <array>
#include <format>
#include <iostream>

#include "../util/print.hpp"

/** Generates the next prime by using the sieve of Eratosthenes. */
int generate_next_prime() {
    static std::array<bool, 123'456'789> sieve;
    static int k = 2;
    for (; k < ssize(sieve); k++) {
        if (not sieve[k]) {
            for (int l = 2*k; l < ssize(sieve); l += k) {
                sieve[l] = true;
            }
            break;
        }
    }
    return k++;
}

int main(int argc, char* argv[]) {
    int n = std::stoi(argv[1]);
    FANCY_PRINT("{}\n", "The first {} prime numbers", n);
    for (int count = 1; count <= n; count++) {
        if (count == 1 or count % 10 == 0) {
            FANCY_PRINT("\n{}", "{:3d}", count);
        }
        auto prime = generate_next_prime();
        PRINT("{} ", prime);
    }
    PRINTLN();
}

