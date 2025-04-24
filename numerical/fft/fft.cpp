#include <complex>

#include "../constants.h"

namespace numerical {
    namespace fft {
        template <typename T>
        T bit_reverse(T a, T bit_size) {
            T result = 0;
            T n = a;
            T i;
        
            for (i = 0; i < bit_size; ++i) {
                result = (result << 1) | (n & 1);
                n >>= 1;
            }
        
            return result;
        }

        void fft(std::complex<double>* arr, std::size_t size) {
            std::size_t i, j, k, n;
            std::size_t order = std::log2(size);
            std::complex<double> temp, w, p, aq;
            std::size_t offset, step, multiplier;
        
            // bit reversed ordering of indices
            for (i = 0; i < size; ++i) {
                n = bit_reverse(i, order);
                if (i < n) {
                    temp = arr[i];
                    arr[i] = arr[n];
                    arr[n] = temp;
                }
            }

            // butterfly computations
            w = {0.0, -2.0 * constants::pi / size};
            w = std::exp(w);
            for (k = 0; k < order; ++k) {
                offset = std::pow(2, k);
                step = 2 * offset;
                multiplier = size / step;
                for (i = 0; i < size; i += step) {
                    for (j = 0; j < offset; ++j) {
                        p = arr[i + j];
                        aq = std::pow(w, multiplier * j) * arr[i + j + offset];
                        arr[i + j] = p + aq;
                        arr[i + j + offset] = p - aq;
                    }
                }
            }
        }
    }
}