#include <stdio.h>

#include "numerical.h"

float func(NumericalVector<float, 2> x) {
    return x[0] * x[0] + x[1] * x[1];
}

class Linmap {
private:
    float (*f)(NumericalVector<float, 2>);
    NumericalVector<float, 2> p0;
    NumericalVector<float, 2> e;

public:
    Linmap(float (*func)(NumericalVector<float, 2>), const NumericalVector<float, 2>& point, const NumericalVector<float, 2>& direction)
     : f(func), p0(point), e(direction) {}

    float operator()(float lambda) {
        printf("%f\n", lambda);
        return f(p0 + e * lambda);
    }
};

template <typename Func>
float optimize(Func f, NumericalVector<float, 2> p0) {
    float lower_bracket = -2.0;
    float upper_bracket = 5.0;
    float tolerance = 1e-4f;
    NumericalVector<float, 2> zero = {0.0, 0.0};
    NumericalVector<float, 2> dir = {0.0, 1.0};
    Linmap lm = {func, zero, dir};

    float res = numerical_optimize_golden_section(lm, lower_bracket, upper_bracket, tolerance);

    return res;
}

double my_func(double x) {
    return (x-1)*(x-2)*(x-3)*(x-4);
}

double my_sine(double x) {
    return std::sin(x);
}

int main() {
    double lower_bracket = -2.0;
    double upper_bracket = 5.0;
    double tolerance = 1e-8f;

    // double res = numerical_optimize_brent(lower_bracket, upper_bracket, my_func, tolerance, 20);

    double res = numerical_integrate_romberg(my_sine, 0.0, NUMERICAL_CONSTANTS_PI_D, 20, tolerance);

    // printf("%f\n", tolerance);
    // float res = numerical_optimize_golden_section(func, lower_bracket, upper_bracket, tolerance);
    // printf("%f\n", res);

    // NumericalVector<float, 2> zero = {0.0, 0.0};
    // float res = optimize(func, zero);

    printf("%f\n", res);

    return 0;
}