#pragma once

#include <array>
#include <cmath>
#include <vector>
#include <cstddef>

#include "numerical/optimize/optimize.h"
#include "numerical/random/xorshift.h"
#include "numerical/sort/sort.h"
#include "numerical/array.cpp"
#include "numerical/constants.h"
#include "numerical/integrate.cpp"
#include "numerical/nvector.h"
#include "numerical/matrix.h"
#include "numerical/ode.cpp"

namespace numerical {
    // array utils
    namespace array {
        template <typename T, std::size_t N> std::array<T, N> linspace(T start, T end);  // new array with N linearly spaced values
    }

    // integration of functions
    namespace integrate {
        template <typename T, typename Func> T romberg(Func f, T a, T b, const std::size_t max_iter, T acc);
    }

    // sort
    namespace sort {
        template <typename T, std::size_t N> void array_insertion(std::array<T, N>& arr);
        template <typename T, typename U, std::size_t N> void cosort_array_insertion(std::array<T, N>& arr, std::array<U, N>& co_arr);
        template <typename T, typename U> void cosort_vector_insertion(std::vector<T>& arr, std::vector<U>& co_arr);
    }

    // optimize
    namespace optimize {
        template <typename T, typename Func> OptimizeResult<T> golden_section(Func function, const T lower_bracket, const T upper_bracket, const T tolerance, const std::size_t max_iterations);
        template <typename T, typename Func> OptimizeResult<T> brent(Func function, const T lower_bracket, const T upper_bracket, const T tolerance, const std::size_t max_iterations);

        template <typename T, typename Func, std::size_t N> NVector<T, N> nelder_mead(Func function, const NVector<T, N> p0, const std::size_t max_iterations);
        template <typename T, typename Func, std::size_t N> NOptimizeResult<T, N> powell(Func function, const NVector<T, N> p0, const std::size_t max_iterations);
    }

    // ordinary differential equations
    namespace ode {
        template <typename T, typename U, typename V, std::size_t N, typename Func> NVector<T, N> runge_kutta(U time, U time_step, NVector<T, N> current_state, Func derivative, V params);
    }
}