#pragma once

#include <array>
#include <cmath>
#include <iostream>
#include <vector>

// constants
#include "numerical/constants.h"

// array utils
template <typename T, std::size_t N> std::array<T, N> numerical_array_linspace(T start, T end);  // new array with N linearly spaced values

#include "numerical/array.cpp"

// integration of functions
template <typename T, typename Func> T numerical_integrate_romberg(Func f, T a, T b, const std::size_t max_iter, T acc);

#include "numerical/integrate.cpp"

// vector
#include "numerical/nvector.h"

// matrix
#include "numerical/matrix.h"

// sort
template <typename T, std::size_t N> void numerical_sort_array_insertion(std::array<T, N>& arr);
template <typename T, typename U, std::size_t N> void numerical_cosort_array_insertion(std::array<T, N>& arr, std::array<U, N>& co_arr);
template <typename T, typename U> void numerical_cosort_vector_insertion(std::vector<T>& arr, std::vector<U>& co_arr);

#include "numerical/sort.cpp"

// optimize
template <typename T, typename Func> T numerical_optimize_golden_section(Func f, T lower_bracket, T upper_bracket, T tolerance);
template <typename T> T numerical_optimize_brent(const T a, const T b, T f(const T), const T tol, const std::size_t max_iter);

#include "numerical/optimize_single.cpp"

template <typename T, std::size_t N, typename Func> NumericalVector<T, N> numerical_optimize_nelder_mead(Func f, NumericalVector<T, N> p0, std::size_t max_iter);

#include "numerical/optimize_multi.cpp"

// ordinary differential equations
template <typename T, typename U, typename V, std::size_t N, typename Func> NumericalVector<T, N> numerical_ode_runge_kutta(U time, U time_step, NumericalVector<T, N> current_state, Func derivative, V params);

#include "numerical/ode.cpp"