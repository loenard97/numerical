#include "../nvector.h"
#include "../mnmatrix.h"

namespace numerical {
    namespace ode {
        template <typename T, typename U, typename Func, typename... Args>
        ODEResult<U, T> RungeKutta::run(Func derivative, T y, U t_start, U t_end, U t_step, Args&&... args) {
            U time = t_start;
            T k1, k2, k3, k4;
            ODEResult<U, T> result;

            if (dense_output) {
                result.dense_time.push_back(time);
                result.dense_y.push_back(y);
            }
    
            while (time < t_end) {
                // clamp step to t_end if it overshoots
                if (time + t_step > t_end) {
                    t_step = t_end - time;
                }

                if constexpr (std::is_invocable_v<Func, U, T>) {
                    k1 = derivative(time, y);
                    k2 = derivative(time + t_step / 2.0, y + k1 * (t_step / 2.0f));
                    k3 = derivative(time + t_step / 2.0, y + k2 * (t_step / 2.0f));
                    k4 = derivative(time + t_step, y + k3 * t_step);
                } else if constexpr (std::is_invocable_v<Func, U, T, Args...>) {
                    k1 = derivative(time, y, std::forward<Args>(args)...);
                    k2 = derivative(time + t_step / 2.0, y + k1 * (t_step / 2.0f), std::forward<Args>(args)...);
                    k3 = derivative(time + t_step / 2.0, y + k2 * (t_step / 2.0f), std::forward<Args>(args)...);
                    k4 = derivative(time + t_step, y + k3 * t_step, std::forward<Args>(args)...);
                } else {
                    static_assert(sizeof...(Args) == 0, "Invalid function signature for derivative function");
                }
                y = y + (k1 + k2 * 2.0 + k3 * 2.0 + k4) * (t_step / 6.0f);

                if (dense_output) {
                    result.dense_time.push_back(time);
                    result.dense_y.push_back(y);
                }

                time += t_step;
            }

            return result;
        }
    }
}