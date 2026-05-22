#include <cmath>

namespace numerical {
    namespace function {
        long fibonacci(long n) {
            double phi = 1.618033988749894848204586834365638118;
            
            return floor(pow(phi, n) / sqrt(5));
        }
    }
}