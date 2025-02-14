#ifndef NUMERICAL_ARRAY_H
#define NUMERICAL_ARRAY_H

#include <array>

template <typename T, std::size_t N>
std::array<T, N> numerical_array_linspace(T start, T end) {
    std::array<T, N> arr;
    T step = (end - start) / N;
    T val = start;

    for (std::size_t i = 0; i < N; ++i) {
        arr[i] = val;
        val += step;
    }

    return arr;
}

#endif