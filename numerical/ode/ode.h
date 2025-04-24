#pragma once

#include <cstddef>

#include "runge_kutta.cpp"

namespace numerical {
    namespace ode {
        template <typename T, typename U, typename V, std::size_t N, typename Func> NVector<T, N> runge_kutta(U time, U time_step, NVector<T, N> current_state, Func derivative, V params);
    }
}