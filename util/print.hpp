#pragma once

#define PRINT(fmt, ...) do {                                    \
    std::cout << std::format((fmt) __VA_OPT__(,) __VA_ARGS__);  \
} while (0)

#define FANCY_PRINT(fmt, ...) do {                                          \
    auto formatted_str = std::format((fmt) __VA_OPT__(,) __VA_ARGS__);      \
    PRINT(" \U0001fb6e\033[7;1m {} \033[0m\U0001fb6c ", formatted_str);     \
} while (0)
