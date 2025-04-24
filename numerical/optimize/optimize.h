#pragma once

#include <cstddef>

#include "util.h"
#include "../nvector.h"

#include "brent.cpp"
#include "golden_section.cpp"
#include "nelder_mead.cpp"
#include "powell.cpp"

namespace numerical {
    namespace optimize {
        template <typename T, typename Func> OptimizeResult<T> golden_section(Func function, const T lower_bracket, const T upper_bracket, const T tolerance, std::size_t max_iterations);
        template <typename T, typename Func> OptimizeResult<T> brent(Func function, const T lower_bracket, const T upper_bracket, const T tolerance, const std::size_t max_iterations);

        template <typename T, typename Func, std::size_t N> NVector<T, N> nelder_mead(Func function, const NVector<T, N> p0, const std::size_t max_iterations);
        template <typename T, typename Func, std::size_t N> NOptimizeResult<T, N> powell(Func function, const NVector<T, N> p0, const T tolerance, const std::size_t max_iterations);
    }
}