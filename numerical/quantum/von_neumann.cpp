#include "../matrix.h"

#include <cstddef>

namespace numerical {
    namespace quantum {
        template <typename T, typename U, std::size_t N>
        Matrix<T, N, N> von_neumann(Matrix<T, N, N> hamiltonian, Matrix<T, N, N> state) {
            std::complex<U> j = {0.0, -1.0};

            return hamiltonian.commute(state) * j;
        }
    }
}