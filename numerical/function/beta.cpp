#include <complex>
#include <cmath>

#include 

namespace numerical {
    namespace function {
        std::complex<double> beta(std::complex<double> z, std::complex<double> w) {
            return gamma(z) * gamma(w) / gamma(z + w);
        }
    }
}