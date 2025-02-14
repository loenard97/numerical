#ifndef NUMERICAL_H
#define NUMERICAL_H

#include <array>
#include <cmath>
#include <iostream>
#include <vector>

// constants
#include "numerical/constants.cpp"

// array utils
template <typename T, std::size_t N> std::array<T, N> numerical_array_linspace(T start, T end);  // new array with N linearly spaced values

#include "numerical/array.cpp"

// vector
#include "numerical/vector.h"

// matrix
#include "numerical/matrix.h"

// sort
template <typename T, std::size_t N> void numerical_sort_array_insertion(std::array<T, N>& arr);
template <typename T, typename U, std::size_t N> void numerical_cosort_array_insertion(std::array<T, N>& arr, std::array<U, N>& co_arr);
template <typename T, typename U> void numerical_cosort_vector_insertion(std::vector<T>& arr, std::vector<U>& co_arr);

#include "numerical/sort.cpp"

// optimize
template <typename T, std::size_t N, typename Func> NumericalVector<T, N> numerical_optimize_nelder_mead(Func f, Vector<T, N> p0, std::size_t max_iter);

#include "numerical/optimize.cpp"

// ordinary differential equations
template <typename T, typename U, typename V, std::size_t N, typename Func> NumericalVector<T, N> numerical_ode_runge_kutta(U time, U time_step, Vector<T, N> current_state, Func derivative, V params);

#include "numerical/ode.cpp"

#endif