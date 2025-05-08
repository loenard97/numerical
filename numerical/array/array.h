#pragma once

#include <array>
#include <cstddef>

#include "array.cpp"

namespace numerical {
    namespace array {
        template <typename T, std::size_t N> std::array<T, N> linspace(T start, T end);
        template <typename T, std::size_t N> std::array<T, N> logspace(T start, T end);

        template <typename T> std::vector<T> linspace(T start, T end, std::size_t num_points);
        template <typename T> std::vector<T> logspace(T start, T end, std::size_t num_points);
    }
}