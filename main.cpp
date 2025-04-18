#include <stdio.h>

#include "numerical.h"

using namespace numerical;

float func(NVector<float, 2> x) {
    return x[0] * x[0] + x[1] * x[1];
}

int main() {
    NVector<float, 2> p0 = {1.0, 1.0};
    optimize::NOptimizeResult<float, 2> res = optimize::powell(func, p0, 5);

    res.display();

    return 0;
}