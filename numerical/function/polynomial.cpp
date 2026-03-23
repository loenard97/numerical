#include <cstdio>
#include <vector>
#include <initializer_list>

namespace numerical {
    namespace function {
        class Polynomial {
        public:
            std::vector<double> coeffs;

            Polynomial() = default;
            Polynomial(std::initializer_list<double> c) : coeffs(c) {}

            double operator()(double x) const {
                double result = 0.0;
                for (auto c : coeffs)
                    result = result * x + c;
                return result;
            }

            void display() {
                printf("Polynomial(");
                for (size_t i = 0; i < coeffs.size(); ++i) {
                    size_t n = coeffs.size() - i - 1;
                    if (n == 0)
                        printf("%g", coeffs[i]);
                    else if (n == 1)
                        printf("%gx + ", coeffs[i]);
                    else 
                        printf("%gx^%d + ", coeffs[i], coeffs.size() - i - 1);
                }
                printf(")\n");
            }
        };
    }
}