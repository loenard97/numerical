#include "../matrix.h"

#include <cstddef>

namespace numerical {
    namespace quantum {
        template <typename T, std::size_t N>
        Matrix<T, N, N> lindblad_dissipator(T gamma, Matrix<T, N, N> lindblad, Matrix<T, N, N> state) {
            Matrix<T, N, N> lindblad_dag = lindblad.dag();
            Matrix<T, N, N> term_1 = lindblad * state * lindblad_dag;
            Matrix<T, N, N> term_2 = lindblad_dag * lindblad;

            return (term_1 - term_2.anticommute(state) * 0.5) * gamma;
        }
    }
}