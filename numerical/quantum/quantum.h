#pragma once

#include <cstddef>
#include <complex>

#include "../mnmatrix.h"
#include "lindblad.cpp"
#include "von_neumann.cpp"

namespace numerical {
    namespace quantum {
        MNMatrix<std::complex<double>, 2, 2> sigma_x = {{0.0, 0.0}, {1.0, 0.0}, {1.0, 0.0}, {0.0, 0.0}};
        MNMatrix<std::complex<double>, 2, 2> sigma_y = {{0.0, 0.0}, {0.0, -1.0}, {0.0, 1.0}, {0.0, 0.0}};
        MNMatrix<std::complex<double>, 2, 2> sigma_z = {{1.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {-1.0, 0.0}};

        template <typename T, typename U, std::size_t N> MNMatrix<T, N, N> von_neumann(MNMatrix<T, N, N> hamiltonian, MNMatrix<T, N, N> state);
        template <typename T, std::size_t N> MNMatrix<T, N, N> lindblad_dissipator(T gamma, MNMatrix<T, N, N> lindblad, MNMatrix<T, N, N> state);
    }
}