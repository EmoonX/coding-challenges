#include <iostream>

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
        return iterator{from, step};
    }
    iterator end() {
        return iterator{to};
    }
};


template<typename T1, typename T2, typename T3 = int>
    requires IntegralAll<T1, T2, T3>
auto range(T1 from, T2 to, T3 step = +1)
    -> Range<typename std::common_type<T1, T2, T3>::type>
{
    return (from, to, step);
}

auto range(auto to) {
    return range(0, to);
}

int main() {
    auto r = range(0, 1123456789U, 1);
    for (auto k : r) {
        //std::cout << k << std::endl;
    }
}
