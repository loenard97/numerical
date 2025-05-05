#pragma once

#include "faddeeva.cpp"

namespace numerical {
    namespace function {
        template <typename T> std::complex<T> faddeeva(std::complex<T> z);
        template <typename T> T voigt(T x, T sigma, T gamma);
    }
}