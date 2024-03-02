#include <array>
#include <format>
#include <iostream>

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
    std::cout << std::format("> The first {} prime numbers:\n", n);
    for (int count = 1; count <= n; count++) {
        if (count == 1 or count % 10 == 0) {
            std::cout << std::format("\n 🭮\033[7;1m {:3d} \033[0m🭬 ", count);
        }
        auto prime = generate_next_prime();
        std::cout << prime << " ";
    }
    std::cout << std::endl;
}

