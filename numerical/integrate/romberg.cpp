#include <cstddef>
#include <cmath>

namespace numerical {
    namespace integrate {
        template <typename T, typename Func>
        T romberg(Func f, T a, T b, const std::size_t max_iter, T acc) {
            T buffer_1[max_iter];
            T buffer_2[max_iter];
            T* Rp = &buffer_1[0];
            T* Rc = &buffer_2[0];
            T step_size = b - a;

            T c = 0.0;
            T n_k;
            std::size_t i, j, epsilon;

            Rp[0] = (f(a) + f(b)) * step_size * 0.5;

            for (i = 1; i < max_iter; ++i) {
                step_size /= 2.0;
                c = 0.0;
                epsilon = 1 << (i-1);
                for (j = 1; j <= epsilon; ++j) {
                    c += f(a + (2*j - 1) * step_size);
                }
                Rc[0] = step_size * c + 0.5 * Rp[0];

                for (j = 1; j <= i; ++j) {
                    n_k = std::pow(4, j);
                    Rc[j] = (n_k * Rc[j-1] - Rp[j-1]) / (n_k - 1);
                }

                if (i > 1 && std::fabs(Rp[i-1] - Rc[i]) < acc) {
                    return Rc[i];
                }

                T *rt = Rp;
                Rp = Rc;
                Rc = rt;
            }

            return Rp[max_iter - 1];
        }

        template <typename T, typename Func>
        T infinite_limit(Func f, T a, T b, const std::size_t max_iter, T acc) {
            double lower_limit = 1.0 / b;
            double upper_limit = 1.0 / a;

            auto g = [f](double x) {
                return f(1.0 / x) / pow(x, 2);
            };

            double res = romberg(g, lower_limit, upper_limit, max_iter, acc);

            return res;
        }
    }
}

/*
namespace numerical {
    namespace integrate {
        template <typename T, typename Func, typename... Args>
        T romberg(Func f, T a, T b, const std::size_t max_iter, T acc, Args&&... args) {
            T buffer_1[max_iter];
            T buffer_2[max_iter];
            T* Rp = &buffer_1[0];
            T* Rc = &buffer_2[0];
            T step_size = b - a;

            T c = 0.0;
            T n_k;
            std::size_t i, j, epsilon;

            if constexpr (std::is_invocable_v<Func, T>) {
                Rp[0] = (f(a) + f(b)) * step_size * 0.5;
            } else if constexpr (std::is_invocable_v<Func, T, Args...>) {
                Rp[0] = (f(a, std::forward<Args>(args)...) + f(b, std::forward<Args>(args)...)) * step_size * 0.5;
            } else {
                static_assert(sizeof...(Args) == 0, "Invalid function signature for derivative function");
            }

            for (i = 1; i < max_iter; ++i) {
                step_size /= 2.0;
                c = 0.0;
                epsilon = 1 << (i-1);
                for (j = 1; j <= epsilon; ++j) {
                    if constexpr (std::is_invocable_v<Func, T, T>) {
                        c += f(a + (2*j - 1) * step_size);
                    } else if constexpr (std::is_invocable_v<Func, T, T, Args...>) {
                        c += f(a + (2*j - 1) * step_size, std::forward<Args>(args)...);
                    } else {
                        static_assert(sizeof...(Args) == 0, "Invalid function signature for derivative function");
                    }
                }
                Rc[0] = step_size * c + 0.5 * Rp[0];

                for (j = 1; j <= i; ++j) {
                    n_k = std::pow(4, j);
                    Rc[j] = (n_k * Rc[j-1] - Rp[j-1]) / (n_k - 1);
                }

                if (i > 1 && std::fabs(Rp[i-1] - Rc[i]) < acc) {
                    return Rc[i];
                }

                T *rt = Rp;
                Rp = Rc;
                Rc = rt;
            }

            return Rp[max_iter - 1];
        }
    }
}
*/