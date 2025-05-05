#pragma once

#include <cstddef>
#include <vector>

#include "dormand_prince.cpp"

namespace numerical {
    namespace ode {
        template <typename T, typename U, typename V, typename Func>
        class RungeKutta {
        public:
            bool dense_output = false;
            std::vector<U> dense_time;
            std::vector<T> dense_y;

            RungeKutta() {};
    
            T run(Func derivative, T y, U t_start, U t_end, U t_step, V params);
            void display_dense_output();
        };
    }
}

#include "runge_kutta.cpp"