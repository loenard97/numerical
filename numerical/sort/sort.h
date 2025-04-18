#pragma once

#include <cstddef>

#include "insertion.cpp"

namespace numerical {
    namespace sort {
        template <typename T, std::size_t N> void array_insertion(std::array<T, N>& arr);
        template <typename T, typename U, std::size_t N> void cosort_array_insertion(std::array<T, N>& arr, std::array<U, N>& co_arr);
        template <typename T, typename U> void cosort_vector_insertion(std::vector<T>& arr, std::vector<U>& co_arr);
    }
}