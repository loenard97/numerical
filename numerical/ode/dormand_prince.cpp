#include <cmath>
#include <vector>

#include "../nvector.h"

namespace numerical {
    namespace ode {
        template <typename T, std::size_t N>
        class DormandPrince {
        private:
            // Dormand Prince Butcher tableau
            const double a[7] = { 0, 1.0 / 5.0, 3.0 / 10.0, 4.0 / 5.0, 8.0 / 9.0, 1.0, 1.0 };
            const double b[7][6] = {
                { },
                { 1.0 / 5.0 },
                { 3.0 / 40.0,        9.0 / 40.0 },
                { 44.0 / 45.0,      -56.0 / 15.0,       32.0 / 9.0 },
                { 19372.0 / 6561.0, -25360.0 / 2187.0,  64448.0 / 6561.0,   -212.0 / 729.0 },
                { 9017.0 / 3168.0,  -355.0 / 33.0,      46732.0 / 5247.0,    49.0 / 176.0,  -5103.0 / 18656.0 },
                { 35.0 / 384.0,      0.0,               500.0 / 1113.0,      125.0 / 192.0, -2187.0 / 6784.0,   11.0 / 84.0 }, 
            };
            const double c_high[7] = { 35.0 / 384.0, 0.0, 500.0 / 1113.0, 125.0 / 192.0, -2187.0 / 6784.0, 11.0 / 84.0, 0.0 };
            const double c_low[7] = { 5179.0 / 57600.0, 0.0, 7571.0 / 16695.0, 393.0 / 640.0, -92097.0 / 339200.0, 187.0 / 2100.0, 1.0 / 40.0 };
            const double d[7] = {
                -12715105075.0 / 11282082432.0,
                0.0, 
                87487479700.0 / 32700410799.0,
                -10690763975.0 / 1880347072.0,
                701980252875.0 / 199316789632.0,
                -1453857185.0 / 822651844.0,
                69997945.0 / 29380423.0,
            };

        public:
            double min_step_change = 0.01;
            double max_step_change = 5.0;
            std::vector<double> time;
            std::vector<NVector<T, N>> data;

            std::vector<NVector<T, N>> data_k0;
            std::vector<NVector<T, N>> data_k1;
            std::vector<NVector<T, N>> data_k2;
            std::vector<NVector<T, N>> data_k3;
            std::vector<NVector<T, N>> data_k4;
            std::vector<NVector<T, N>> data_k5;
            std::vector<NVector<T, N>> data_k6;

            // DormandPrince() = default;
            DormandPrince() {};

            template <typename Func>
            void run(Func derivative, NVector<T, N> y, double step_size, const double tolerance, const double t_start, const double t_end, const bool full_output, const bool dense_output) {
                std::size_t i, j;
                double next_step, err;
                double t = t_start;
                NVector<T, N> err_vec;
                NVector<T, N> k[7];
                NVector<T, N> y_temp;
                NVector<T, N> y_high = y;
                NVector<T, N> y_low = y;

                time.clear();
                data.clear();
                data_k0.clear();
                data_k1.clear();
                data_k2.clear();
                data_k3.clear();
                data_k4.clear();
                data_k5.clear();
                data_k6.clear();

                while (t < t_end) {
                    // printf("%f\n", t);
                    // clamp step to t_end if it overshoots
                    if (t + step_size > t_end) {
                        step_size = t_end - t;
                    }

                    // Dormand Prince step
                    k[0] = derivative(t, y);
                    for (i = 1; i < 7; ++i) {
                        y_temp = y;
                        for (j = 0; j < i; ++j) {
                            y_temp = y_temp + k[j] * step_size * b[i][j];
                        }
                        k[i] = derivative(t + a[i] * step_size, y_temp);
                    }
                    for (i = 0; i < 7; ++i) {
                        y_high = y_high + k[i] * (step_size * c_high[i]);
                        y_low  = y_low  + k[i] * (step_size * c_low[i]);
                    }
                    if (dense_output) {
                        data_k0.push_back(k[0]);
                        data_k1.push_back(k[1]);
                        data_k2.push_back(k[2]);
                        data_k3.push_back(k[3]);
                        data_k4.push_back(k[4]);
                        data_k5.push_back(k[5]);
                        data_k6.push_back(k[6]);
                    }

                    // check error of current step
                    err_vec = y_high - y_low;
                    err = 0.0;
                    for (i = 0; i < N; ++i) {
                        err = std::max(err, std::abs(err_vec[i]));
                    }

                    // accept step
                    if (err <= tolerance) {
                        t += step_size;
                        y = y_high;
                        if (full_output || dense_output) {
                            data.push_back(y);
                            time.push_back(t);
                        }
                    }

                    // update step size
                    next_step = 0.9 * std::pow(tolerance / (err + 1e-12), 0.2);
                    if (next_step < min_step_change) {
                        next_step = min_step_change;
                    }
                    if (next_step > max_step_change) {
                        next_step = max_step_change;
                    }
                    step_size *= next_step;
                }
            }

            template <typename Func>
            void run_dense(Func derivative, NVector<T, N> y, double step_size, const double tolerance, const double t_start, const double t_end) {
                std::size_t i, j;
                double next_step, err;
                double t = t_start;
                NVector<T, N> err_vec;
                NVector<T, N> k[7];
                NVector<T, N> y_temp;
                NVector<T, N> y_high = y;
                NVector<T, N> y_low = y;

                time.clear();
                data.clear();
                data_k0.clear();
                data_k1.clear();
                data_k2.clear();
                data_k3.clear();
                data_k4.clear();
                data_k5.clear();
                data_k6.clear();

                while (t < t_end) {
                    // clamp step to t_end if it overshoots
                    if (t + step_size > t_end) {
                        step_size = t_end - t;
                    }

                    // Dormand Prince step
                    k[0] = derivative(t, y);
                    for (i = 1; i < 7; ++i) {
                        y_temp = y;
                        for (j = 0; j < i; ++j) {
                            y_temp = y_temp + k[j] * step_size * b[i][j];
                        }
                        k[i] = derivative(t + a[i] * step_size, y_temp);
                    }
                    for (i = 0; i < 7; ++i) {
                        y_high = y_high + k[i] * (step_size * c_high[i]);
                        y_low  = y_low  + k[i] * (step_size * c_low[i]);
                    }
                    data.push_back(y);
                    time.push_back(t);

                    t += step_size;
                    y = y_high;
                }
            }

            template <std::size_t M>
            std::vector<NVector<T, N>> dense_output(std::array<double, M> time_arr) {
                std::size_t i = 0;
                std::size_t j;
                std::size_t k = 0;
                double t0, h, theta;
                NVector<T, N> temp;
                std::vector<NVector<T, N>> result;

                while (true) {
                    t0 = time[i];
                    h = time[i + 1] - t0;
                    theta = (time_arr[k] - t0) / h;
                    if (theta >= 1.0) {
                        ++i;
                        continue;
                    }

                    // temp = data[i] * (1.0 - theta) + data[i + 1] * theta;
                    /*
                    temp = temp + (
                        data_k0[i] * d[0] * theta + 
                        data_k1[i] * d[1] * theta * theta + 
                        data_k2[i] * d[2] * theta * theta * theta + 
                        data_k3[i] * d[3] * theta * theta * theta * theta + 
                        data_k4[i] * d[4] * theta * theta * theta * theta * theta + 
                        data_k5[i] * d[5] * theta * theta * theta * theta * theta * theta
                    ) * h;
                    */
                    temp = data[i] * (1.0 - theta) + data[i + 1] * theta + ((data[i + 1] - data[i]) * (1.0 - 2.0*theta) + data_k0[i] * (theta - 1.0) + data_k6[i] * theta) * theta * (theta - 1.0);
                    result.push_back(temp);

                    ++k;
                    if (k >= M) {
                        break;
                    }
                }

                return result;
            }
        };
    }
}