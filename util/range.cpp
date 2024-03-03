#include <cstdint>
#include <iostream>
#include <type_traits>

template<typename T> requires std::integral<T>
struct Range {
    T from, to, step;

    struct iterator {
        T num, step;

        T operator*() {
            return num;
        }
        T& operator++() {
            num += step;
            return this->num;
        }
        bool operator!=(const iterator& other) {
            return (step > 0) ? num < other.num : num > other.num;
        }
    };

    iterator begin() {
        return iterator{from, step};
    }
    iterator end() {
        return iterator{to};
    }
};

template<typename T> requires std::integral<T>
Range<T> range(T to) {
    return range(0, to);
}

template<typename T> requires std::integral<T>
Range<T> range(T from, T to, T step = +1) {
    return {from, to, step};
}

int main() {
    for (auto&& k : range(20, 10, -2)) {
        std::cout << k << std::endl;
    }
}
