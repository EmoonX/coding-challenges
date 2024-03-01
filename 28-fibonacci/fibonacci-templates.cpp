#include <cstdint>
#include <format>
#include <iostream>

/** 
 * Template for the Fibonacci struct
 * 
 * `Fibonacci<N>` holds the `N`th Fibonacci value at compile time
 */
template<int N>
struct Fibonacci {
    static constexpr int64_t value =
        Fibonacci<N-1>::value + Fibonacci<N-2>::value;
};
template<>
struct Fibonacci<1> {
    static constexpr int64_t value = 1;
};
template<>
struct Fibonacci<0> {
    static constexpr int64_t value = 0;
};

/** `print_fib<N>`: prints the `N`th Fibonacci value */
template<int N>
void print_fib() {
    std::cout << std::format("fib({}) = {}\n", N, Fibonacci<N>::value);
}

int main() {
    print_fib<0>();
    print_fib<1>();
    print_fib<2>();
    print_fib<3>();
    print_fib<4>();
    print_fib<8>();
    print_fib<16>();
    print_fib<32>();
    print_fib<64>();
    print_fib<90>();
}

