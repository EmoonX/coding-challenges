#pragma once

#include <format>
#include <iostream>

/** Prints a formatted string. */
#define PRINT(fmt, ...) do {                                        \
    std::cout << std::format((fmt) __VA_OPT__(,) __VA_ARGS__);      \
} while (0)

/** Prints either a formatted string or nothing, appending a newline. */
#define PRINTLN(...) do {               \
    __VA_OPT__(PRINT(__VA_ARGS__));     \
    std::cout << std::endl;             \
} while (0)

/** Fancy-prints a formatted string.
 *  - `fmt_outer`: wrapper format string, should contain exactly one `{}`
 *  - `fmt_inner`: the part to be stylized, supplied with format args   */
#define FANCY_PRINT(fmt_outer, fmt_inner, ...) do {                         \
    auto inner_str = std::format((fmt_inner) __VA_OPT__(,) __VA_ARGS__);    \
    auto fancy_str = std::format(                                           \
        "\U0001fb6e\033[7;1m {} \033[0m\U0001fb6c", inner_str               \
    );                                                                      \
    PRINT(fmt_outer, fancy_str);                                            \
} while (0)
