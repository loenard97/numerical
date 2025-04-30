/*! \file ode.cpp
    
    ordinary differential equation solvers
*/

#include "../nvector.h"
#include "../mnmatrix.h"

namespace numerical {
    namespace ode {
        class RungeKutta {
        public:
            RungeKutta() {};

            template <typename T, typename U, typename V, typename Func>
            T run(Func derivative, T y, const U t_start, const U t_end, U t_step, V params) {
                U time = t_start;
                T k1, k2, k3, k4;
        
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
                    time += t_step;
                }

                return y;
            }
        };
    }
}