#include <concepts>

template<typename... Types>
concept IntegralAll = (std::is_integral<Types>::value && ...);

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
        return iterator(from, step);
    }
    iterator end() {
        return iterator(to);
    }
};

auto range(auto to) {
    return range(0, to);
}

template<typename T1, typename T2, typename T3>
    requires IntegralAll<T1, T2, T3>
auto range(T1 from, T2 to, T3 step = +1) {
    using T = std::common_type<T1, T2, T3>::type;
    return Range<T>(from, to, step);
}

int main() {
    for (auto k : range(0, 1123456789LL, 2ULL)) {
        //std::cout << k << std::endl;
    }
}
