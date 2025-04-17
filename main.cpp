#include <stdio.h>

#include "numerical.h"

using namespace numerical;

float func(NVector<float, 2> x) {
    return x[0] * x[0] + x[1] * x[1];
}

class Linmap {
private:
    float (*f)(NVector<float, 2>);
    NVector<float, 2> p0;
    NVector<float, 2> e;

public:
    Linmap(float (*func)(NVector<float, 2>), const NVector<float, 2>& point, const NVector<float, 2>& direction)
     : f(func), p0(point), e(direction) {}

    float operator()(float lambda) {
        printf("%f\n", lambda);
        return f(p0 + e * lambda);
    }
};

template <typename Func>
float optimize(Func f, NVector<float, 2> p0) {
    float lower_bracket = -2.0;
    float upper_bracket = 5.0;
    float tolerance = 1e-4f;
    NVector<float, 2> zero = {0.0, 0.0};
    NVector<float, 2> dir = {0.0, 1.0};
    Linmap lm = {func, zero, dir};

    float res = optimize::golden_section(lm, lower_bracket, upper_bracket, tolerance, 20);

    return res;
}

double my_func(double x) {
    return (x-1)*(x-2)*(x-3)*(x-4);
}

int main() {
    double lower_bracket = -2.0;
    double upper_bracket = 5.0;
    double tolerance = 1e-8f;

    optimize::OptimizeResult<double> res = optimize::brent(my_func, lower_bracket, upper_bracket, tolerance, 20);

    // double res = integrate::romberg(std::sin, 0.0, constants::pi_double, 20, tolerance);

    // printf("%f\n", tolerance);
    // float res = numerical_optimize_golden_section(func, lower_bracket, upper_bracket, tolerance);
    // printf("%f\n", res);

    // NVector<float, 2> zero = {0.0, 0.0};
    // float res = optimize(func, zero);

    printf("%f\n", res.x);

    return 0;
}