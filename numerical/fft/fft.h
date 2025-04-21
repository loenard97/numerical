#pragma once

#include <complex>

#include "fft.cpp"

namespace numerical {
    namespace fft {
        void fft(std::complex<double>* arr, std::size_t size);
    }
}