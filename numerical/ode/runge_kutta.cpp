/*! \file ode.cpp
    
    ordinary differential equation solvers
*/

#include "../nvector.h"
#include "../mnmatrix.h"

namespace numerical {
    namespace ode {
        template <typename T, typename U, typename V, typename Func>
        T RungeKutta<T, U, V, Func>::run(Func derivative, T y, U t_start, U t_end, U t_step, V params) {
            U time = t_start;
            T k1, k2, k3, k4;

            dense_time.clear();
            dense_y.clear();

            if (dense_output) {
                dense_time.push_back(time);
                dense_y.push_back(y);
            }
    
            while (time < t_end) {
                // clamp step to t_end if it overshoots
                if (time + t_step > t_end) {
                    t_step = t_end - time;
                }

                k1 = derivative(time, y, params);
                k2 = derivative(time + t_step / 2.0, y + k1 * (t_step / 2.0f), params);
                k3 = derivative(time + t_step / 2.0, y + k2 * (t_step / 2.0f), params);
                k4 = derivative(time + t_step, y + k3 * t_step, params);
                y = y + (k1 + k2 * 2.0 + k3 * 2.0 + k4) * (t_step / 6.0f);

                if (dense_output) {
                    dense_time.push_back(time);
                    dense_y.push_back(y);
                }

                time += t_step;
            }

            return y;
        }

        template <typename T, typename U, typename V, typename Func>
        void RungeKutta<T, U, V, Func>::display_dense_output() {
            std::size_t i, j;
            std::size_t N = dense_y[0].size();

            printf("# time, # y");
            for (i = 0; i < dense_time.size(); ++i) {
                printf("%f, ", dense_time[i]);
                dense_y[i].display_csv();
                printf("\n");
            }
        }
    }
}