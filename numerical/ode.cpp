#ifndef NUMERICAL_ODE_H
#define NUMERICAL_ODE_H

#include "vector.h"

// 4th order Runge-Kutta
template <typename T, typename U, typename V, std::size_t N, typename Func>
Vector<T, N> numerical_ode_runge_kutta(U time, U time_step, Vector<T, N> current_state, Func derivative, V params) {
    Vector<T, N> k1, k2, k3, k4;

    k1 = derivative(time, current_state, params);
    k2 = derivative(time + time_step / 2.0, current_state + k1 * (time_step / 2.0f), params);
    k3 = derivative(time + time_step / 2.0, current_state + k2 * (time_step / 2.0f), params);
    k4 = derivative(time + time_step, current_state + k3 * time_step, params);

    return current_state + (k1 + k2 * 2.0 + k3 * 2.0 + k4) * (time_step / 6.0f);
}

#endif