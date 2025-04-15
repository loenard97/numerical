#include <iostream>
#include <cmath>
#include "../numerical.h"
#include "util.h"

double func_quadratic(double x) {
    return (x - 3) * (x - 3) + 2;
}

double func_absolute(double x) {
    if (x > 0) {
        return x;
    }
    if (x < 0) {
        return -x;
    }
    return 0.0;
}

double func_cubic(double x) {
    return (x - 1) * (x - 1) * (x - 1) - x + 1;
}

double func_rastrigin(double x) {
    return x * x - 10 * std::cos(2 * NUMERICAL_CONSTANTS_PI * x) + 10;
}

int main() {
    double lower_bound, upper_bound, tolerance, res;

    // quadratic function
    lower_bound = 0.0;
    upper_bound = 5.0;
    tolerance = 1e-5;
    res = numerical_optimize_brent(lower_bound, upper_bound, func_quadratic, tolerance, 100);
    ASSERT_NEAR_EQUAL(res, 3.0, tolerance);

    // absolute value function
    lower_bound = -10.0;
    upper_bound = 10.0;
    tolerance = 1e-5;
    res = numerical_optimize_brent(lower_bound, upper_bound, func_absolute, tolerance, 100);
    ASSERT_NEAR_EQUAL(res, 0.0, tolerance);

    // cubic function
    lower_bound = -1.0;
    upper_bound = 3.0;
    tolerance = 1e-5;
    res = numerical_optimize_brent(lower_bound, upper_bound, func_cubic, tolerance, 100);
    ASSERT_NEAR_EQUAL(res, 1.577346, tolerance);

    // rastrigin function
    lower_bound = -3.0;
    upper_bound = 3.0;
    tolerance = 1e-5;
    res = numerical_optimize_brent(lower_bound, upper_bound, func_rastrigin, tolerance, 100);
    ASSERT_NEAR_EQUAL(res, 0.0, tolerance);

    // printf("%f\n", res);
}