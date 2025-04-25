#pragma once

#include <cstddef>
#include <complex>

#include "../matrix.h"
#include "lindblad.cpp"
#include "von_neumann.cpp"

namespace numerical {
    namespace quantum {
        Matrix<std::complex<double>, 2, 2> sigma_x = {{0.0, 0.0}, {1.0, 0.0}, {1.0, 0.0}, {0.0, 0.0}};
        Matrix<std::complex<double>, 2, 2> sigma_y = {{0.0, 0.0}, {0.0, -1.0}, {0.0, 1.0}, {0.0, 0.0}};
        Matrix<std::complex<double>, 2, 2> sigma_z = {{1.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {-1.0, 0.0}};

        template <typename T, typename U, std::size_t N> Matrix<T, N, N> von_neumann(Matrix<T, N, N> hamiltonian, Matrix<T, N, N> state);
        template <typename T, std::size_t N> Matrix<T, N, N> lindblad_dissipator(T gamma, Matrix<T, N, N> lindblad, Matrix<T, N, N> state);
    }
}