#include <complex>
#include <cmath>

namespace numerical {
    namespace function {
        std::complex<double> gamma(std::complex<double> z0) {
            double pi = 3.141592653589793;
            double coeffs[9] {
                0.99999999999980993,
                676.5203681218851,
                -1259.1392167224028,
                771.32342877765313,
                -176.61502916214059,
                12.507343278686905,
                -0.13857109526572012,
                9.9843695780195716e-6,
                1.5056327351493116e-7,
            };

            if (z0.real() < 0.5)
                return pi / (sin(pi * z0) * gamma(1.0 - z0));
            
            std::complex<double> z = z0 - 1.0;
            std::complex<double> x = {coeffs[0], 0.0};
            for (size_t i = 1; i < 9; ++i)
                x += coeffs[i] / (z + std::complex<double>(i));

            std::complex<double> t = z + 7.5;
            return sqrt(2.0 * pi) * pow(t, z + 0.5) * exp(-t) * x;
        }

        std::complex<double> beta(std::complex<double> z, std::complex<double> w) {
            return gamma(z) * gamma(w) / gamma(z + w);
        }

        long factorial(long n) {
            std::complex<double> z = {n + 1, 0.0};

            return round(gamma(z).real());
        }

        long binomial(long n, long k) {
            if (k > n)
                return 0;
            
            return factorial(n) / (factorial(k) * factorial(n - k));
        }

        long fibonacci(long n) {
            double phi = 1.618033988749894848204586834365638118;
            
            return floor(pow(phi, n) / sqrt(5));
        }
    }
}