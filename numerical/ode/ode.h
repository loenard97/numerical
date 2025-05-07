/*! \file ode.h
    
    ordinary differential equation solvers
*/

#pragma once

#include <cstddef>
#include <vector>

#include "dormand_prince.cpp"

namespace numerical {
    namespace ode {
        template<typename U, typename T>
        class ODEResult {
        public:
            U end_time;
            T end_y;
            std::vector<U> dense_time;
            std::vector<T> dense_y;

            void display_dense_output() {
                std::size_t i, j;
                std::size_t N = dense_y[0].size();

                printf("# time, # y\n");
                for (i = 0; i < dense_time.size(); ++i) {
                    printf("%f, ", dense_time[i]);
                    dense_y[i].display_csv();
                    printf("\n");
                }
            }
        };

        class RungeKutta {
        public:
            bool dense_output = false;

            RungeKutta() {};
    
            template <typename T, typename U, typename Func, typename... Args> ODEResult<U, T> run(Func derivative, T y, U t_start, U t_end, U t_step, Args&&... params);
        };
    }
}

#include "runge_kutta.cpp"