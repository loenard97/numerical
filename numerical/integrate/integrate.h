#pragma once

#include <cstddef>

#include "romberg.cpp"

namespace numerical {
    namespace integrate {
        template <typename T, typename Func> T romberg(Func f, T a, T b, const std::size_t max_iter, T acc);
    }
}