#include <cstdint>
#include <format>
#include <iostream>
#include <vector>

#include "../util/print.hpp"

/** Our prime number generator. */
struct PrimeGenerator {
    /** The sieve of Eratosthenes. Uses `uint8_t` instead of `bool` to
     *  avoid the stupid inefficient `std::vector<bool>`  specialization. */
    std::vector<uint8_t> sieve = std::vector<uint8_t>(123'456'789);

    /** The last-generated prime number. */
    int last_prime = -1;

    /** Generates the next prime number. */
    int next_prime() {
        if (last_prime == -1) {
            last_prime = 2;
            return 2;
        }
        int k = (last_prime == 2) ? 3 : last_prime + 2;
        for (; k < ssize(sieve); k += 2) {
            if (not sieve[k]) {
                for (int l = 2*k; l < ssize(sieve); l += k) {
                    sieve[l] = true;
                }
                last_prime = k;
                break;
            }
        }
        return k;
    }
};

int main(int argc, char* argv[]) {
    int n = std::stoi(argv[1]);    
    PRINT("The first {} prime numbers:\n", n);

    auto gen = PrimeGenerator();
    for (int count = 1; count <= n; count++) {
        if (count == 1 or count % 10 == 0) {
            FANCY_PRINT("\n {} ", "{:3d}", count);
        }
        auto prime = gen.next_prime();
        PRINT("{} ", prime);
    }
    PRINTLN();
}

