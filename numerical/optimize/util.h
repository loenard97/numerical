#pragma once

#include <cstddef>

#include "../nvector.h"

namespace numerical {
    namespace optimize {
        template <typename T>
        struct OptimizeResult {
            T x;
            T fx;
            std::size_t iterations;
        };

        template <typename T, std::size_t N>
        struct NOptimizeResult {
            NVector<T, N> x;
            T fx;
            std::size_t iterations;

            void display() {
                std::cout << "NOptimizeResult(\n\t";
                this->x.display();
                std::cout << "\t" << this->fx << ",\n";
                std::cout << "\t" << this->iterations << ",\n";
                std::cout << ")\n";
            }
        };

        template <typename T, typename Func, std::size_t N>
        class LinearMap {
        public:
            Func function;
            NVector<T, N> position;
            NVector<T, N> direction;

            LinearMap() = default;
            LinearMap(Func function, const NVector<T, N>& position, const NVector<T, N>& direction)
                : function(function), position(position), direction(direction) {}

            T operator()(T lambda) {
                return function(position + direction * lambda);
            }
        };
    }
}