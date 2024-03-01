#include <cstdint>
#include <format>
#include <iostream>
#include <vector>

/** Calculates the `n`th Fibonacci number */
int64_t fibonacci(int n) {
    static std::vector<int64_t> fib(n+1, -1);
    if (fib[n] != -1) {
        return fib[n];
    }
    if (n == 0 or n == 1) {
        return n;
    }
    fib[n] = fibonacci(n-2) + fibonacci(n-1);
    return fib[n];
}

int main(int argc, char* argv[]) {
    int n;
    try {
        n = std::stoi(argv[1]);
        if (n < 0 or n > 90) {
            throw std::invalid_argument("");
        }
    } catch (...) {
        std::cerr << "Please input valid N (between 0 and 90) as argument\n";
        exit(EXIT_FAILURE);
    }
    std::cout << std::format("fib({}) = {}\n", n, fibonacci(n));
}

