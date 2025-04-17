/*! \file ode.cpp
    
    ordinary differential equation solvers
*/

#include "nvector.h"

namespace numerical {
    namespace ode {
        /*! \fn NumericalVector<T, N> numerical_ode_runge_kutta(U time, U time_step, NumericalVector<T, N> current_state, Func derivative, V params)
            \param fd The descriptor to close.
        
            4th order Runge-Kutta.
        */
        template <typename T, typename U, typename V, std::size_t N, typename Func>
        NVector<T, N> runge_kutta(U time, U time_step, NVector<T, N> current_state, Func derivative, V params) {
            NVector<T, N> k1, k2, k3, k4;
        
            k1 = derivative(time, current_state, params);
            k2 = derivative(time + time_step / 2.0, current_state + k1 * (time_step / 2.0f), params);
            k3 = derivative(time + time_step / 2.0, current_state + k2 * (time_step / 2.0f), params);
            k4 = derivative(time + time_step, current_state + k3 * time_step, params);
        
            return current_state + (k1 + k2 * 2.0 + k3 * 2.0 + k4) * (time_step / 6.0f);
        }
    }
}