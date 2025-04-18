#include <cstddef>

#include "../nvector.h"
#include "optimize.h"
#include "util.h"

namespace numerical {
    namespace optimize {
        template <typename T, typename Func, std::size_t N>
        NOptimizeResult<T, N> powell(Func function, const NVector<T, N> p0, const std::size_t max_iterations) {
            T lower_bracket = -10.0;
            T upper_bracket = 10.0;
            T tolerance = 1e-4f;
            std::size_t i, j;

            std::vector<NVector<T, N>> basis_vectors;
            LinearMap<T, Func, N> mapped_function;
            NOptimizeResult<T, N> result;
            OptimizeResult<T> linear_result;
            NVector<T, N> unit_vector;
            NVector<T, N> current_point = p0;

            mapped_function.function = function;
            mapped_function.position = current_point;
            for (i = 0; i < N; ++i) {
                unit_vector = NVector<T, N>::zero();
                unit_vector[i] = 1.0;
                basis_vectors.push_back(unit_vector);
            }

            for (i = 0; i < max_iterations; ++i) {
                for (j = 0; j < N; ++j) {
                    mapped_function.direction = basis_vectors[j];
                    linear_result = brent(mapped_function, lower_bracket, upper_bracket, tolerance, 5);
                    current_point = current_point + basis_vectors[j] * linear_result.x;
                    current_point.display();
                }
                mapped_function.position = current_point;
            }

            result.x = current_point;
            result.fx = function(current_point);
            result.iterations = i;

            return result;
        }
    }
}