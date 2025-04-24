#include <cstddef>

#include "../nvector.h"
#include "optimize.h"

namespace numerical {
    namespace optimize {
        template <typename T, typename Func, std::size_t N>
        NOptimizeResult<T, N> powell(Func function, const NVector<T, N> p0, const T tolerance, const std::size_t max_iterations) {
            std::size_t i, j;
            T lower_bracket = -10.0;
            T upper_bracket = 10.0;

            NVector<T, N> basis_vectors[N];  // basis vectors along which to search
            NVector<T, N> points[N + 1];  // points where function is evaluated
            T function_vals[N + 1];  // function values at each point
            T f1, f2, f3;  // special function values to check efficiency of basis_vectors
            points[0] = p0;
            std::size_t max_delta_idx = 0;
            T max_delta = 0;
            T deltas[N];  // how much the function value decreases for each direction
            NVector<T, N> epsilon;

            LinearMap<T, Func, N> mapped_function;
            mapped_function.function = function;
            OptimizeResult<T> linear_result;
            NOptimizeResult<T, N> result;

            // first guess basis vectors
            for (i = 0; i < N; ++i) {
                basis_vectors[i] = NVector<T, N>::zero();
                basis_vectors[i][i] = 1.0;
            }

            for (i = 0; i < max_iterations; ++i) {
                // line searches along each basis_vector
                function_vals[0] = function(points[0]);
                for (j = 0; j < N; ++j) {
                    mapped_function.position = points[j];
                    mapped_function.direction = basis_vectors[j];
                    linear_result = brent(mapped_function, lower_bracket, upper_bracket, tolerance, 5);
                    function_vals[j + 1] = linear_result.fx;
                    points[j + 1] = points[j] + basis_vectors[j] * linear_result.x;
                    deltas[j] = function_vals[j] - function_vals[j + 1];
                }

                // find best direction so far
                max_delta_idx = 0;
                max_delta = deltas[0];
                for (j = 0; j < N; ++j) {
                    if (deltas[j] > max_delta) {
                        max_delta_idx = j;
                        max_delta = deltas[j];
                    }
                }

                // check if convergence was reached
                if (max_delta < tolerance) {
                    break;
                }

                // check if current basis_vectors are efficient or can be improved
                f1 = function_vals[0];
                f2 = function_vals[N];
                f3 = function(points[N] * 2.0 - points[0]);
                if (f3 >= f1 || (f1 - 2.0*f2 + f3)*std::pow(f1 - f2 - max_delta, 2) >= 0.5*max_delta*std::pow(f1 - f3, 2)) {
                    points[0] = points[N];
                } else {
                    epsilon = points[N] - points[0];
                    mapped_function.position = points[N];
                    mapped_function.direction = epsilon;
                    linear_result = brent(mapped_function, lower_bracket, upper_bracket, tolerance, 5);
                    for (j = max_delta_idx; j < N - 1; ++j) {
                        basis_vectors[j] = basis_vectors[j + 1];
                    }
                    basis_vectors[N - 1] = epsilon;
                    points[0] = points[N] + epsilon * linear_result.x;
                }
            }

            result.x = points[N];
            result.fx = function(points[N]);
            result.iterations = i;

            return result;
        }
    }
}