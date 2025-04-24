#pragma once

#include <array>
#include <cstddef>

#include "array.cpp"

namespace numerical {
    namespace array {
        template <typename T, std::size_t N> std::array<T, N> linspace(T start, T end);
        template <typename T, std::size_t N> std::array<T, N> logspace(T start, T end);
    }
}