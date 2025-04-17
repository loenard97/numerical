#pragma once

#define NUMERICAL_UTIL_SWAP SWAP(x, y, T) do { T SWAP = x; x = y; y = SWAP; } while (0)
#define NUMERICAL_UTIL_SIGN(x) ((a < 0) ? (-1.0) : (1.0))

template <typename T>
T numerical_util_sign(T value) {
    if (value == 0) {
        return static_cast<T>(0);
    }
    if (value > 0) {
        return static_cast<T>(1);
    }
    return static_cast<T>(-1);
}