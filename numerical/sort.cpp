#ifndef NUMERICAL_SORT_H
#define NUMERICAL_SORT_H

#include <array>

template <typename T, std::size_t N>
void numerical_sort_array_insertion(std::array<T, N>& arr) {
    std::size_t j;
    for (std::size_t i = 1; i < N; ++i) {
        T temp;
        j = i;
        while (j > 0 && arr[j] < arr[j - 1]) {
            temp = arr[j];
            arr[j] = arr[j - 1];
            arr[j - 1] = temp;
            j -= 1;
        }
    }
}

template <typename T, typename U, std::size_t N>
void numerical_cosort_array_insertion(std::array<T, N>& arr, std::array<U, N>& co_arr) {
    std::size_t j;
    for (std::size_t i = 1; i < N; ++i) {
        T temp;
        j = i;
        while (j > 0 && arr[j] < arr[j - 1]) {
            temp = arr[j];
            arr[j] = arr[j - 1];
            arr[j - 1] = temp;

            temp = co_arr[j];
            co_arr[j] = co_arr[j - 1];
            co_arr[j - 1] = temp;

            j -= 1;
        }
    }
}

template <typename T, typename U>
void numerical_cosort_vector_insertion(std::vector<T>& arr, std::vector<U>& co_arr) {
    std::size_t N = arr.size();
    std::size_t j;

    for (std::size_t i = 1; i < N; ++i) {
        T temp;
        U co_temp;
        j = i;
        while (j > 0 && arr.at(j) < arr.at(j - 1)) {
            temp = arr.at(j);
            arr.at(j) = arr.at(j - 1);
            arr.at(j - 1) = temp;

            co_temp = co_arr.at(j);
            co_arr.at(j) = co_arr.at(j - 1);
            co_arr.at(j - 1) = co_temp;

            j -= 1;
        }
    }
}

#endif