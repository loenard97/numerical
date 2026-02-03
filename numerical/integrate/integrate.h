#pragma once

#include <cstddef>

#include "romberg.cpp"

namespace numerical {
    namespace integrate {
        // template <typename T, typename Func, typename... Args> T romberg(Func f, T a, T b, const std::size_t max_iter, T acc, Args&&... args);
        template <typename T, typename Func> T romberg(Func f, T a, T b, const std::size_t max_iter, T acc);
        template <typename T, typename Func> T infinite_limit(Func f, T a, T b, const std::size_t max_iter, T acc);
    }
}