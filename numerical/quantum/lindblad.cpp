#include "../mnmatrix.h"

#include <cstddef>

namespace numerical {
    namespace quantum {
        template <typename T, std::size_t N>
        MNMatrix<T, N, N> lindblad_dissipator(T gamma, MNMatrix<T, N, N> lindblad, MNMatrix<T, N, N> state) {
            MNMatrix<T, N, N> lindblad_dag = lindblad.dag();
            MNMatrix<T, N, N> term_1 = lindblad * state * lindblad_dag;
            MNMatrix<T, N, N> term_2 = lindblad_dag * lindblad;

            return (term_1 - term_2.anticommute(state) * 0.5) * gamma;
        }
    }
}