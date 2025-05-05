#include <complex>
#include <vector>

namespace numerical {
    namespace function {
        //! Weideman 1994 approximation
        template <typename T>
        std::complex<T> faddeeva(std::complex<T> z) {
            static const int N = 16;
            static const double xk[16] = {
                1.171953619, 3.388508309, 5.552496140, 7.729175500,
                9.919141580, 12.12392209, 14.34402571, 16.57994902,
                18.83217888, 21.10119305, 23.38747062, 25.69149230,
                28.01373941, 30.35469539, 32.71484664, 35.09468212
            };
            static const double ck[16] = {
                0.137776178, 0.137776178, 0.137776178, 0.137776178,
                0.137776178, 0.137776178, 0.137776178, 0.137776178,
                0.137776178, 0.137776178, 0.137776178, 0.137776178,
                0.137776178, 0.137776178, 0.137776178, 0.137776178
            };

            std::complex<double> i(0.0, 1.0);
            std::complex<double> w = 0.0;

            for (int k = 0; k < N; ++k) {
                w += ck[k] / (z - i * xk[k]);
            }

            return 2.0 * w * std::exp(-z*z);
        }

        template <typename T> T
        voigt(T x, T sigma, T gamma) {
            std::complex<T> j = {0.0, 1.0};
            std::complex<T> z = (x + j * gamma) / (std::sqrt(2.0) * sigma);

            return std::real(faddeeva(z)) / (sigma * std::sqrt(2.0 * constants::pi_double));
        }
    }
}