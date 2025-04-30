#include "../mnmatrix.h"

#include <cstddef>

namespace numerical {
    namespace quantum {
        template <typename T, typename U, std::size_t N>
        MNMatrix<T, N, N> von_neumann(MNMatrix<T, N, N> hamiltonian, MNMatrix<T, N, N> state) {
            std::complex<U> j = {0.0, -1.0};

            return hamiltonian.commute(state) * j;
        }
    }
}