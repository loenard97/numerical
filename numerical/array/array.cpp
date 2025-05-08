#include <array>
#include <vector>
#include <cmath>

namespace numerical {
    namespace array {
        //! Array linspace
        //!
        //! Return an array where values are linearly increasing from start to end
        template <typename T, std::size_t N>
        std::array<T, N> linspace(T start, T end) {
            std::array<T, N> arr;
            T step = (end - start) / N;
            T val = start;
        
            for (std::size_t i = 0; i < N; ++i) {
                arr[i] = val;
                val += step;
            }
        
            return arr;
        }

        //! Array logspace
        //!
        //! Return an array where values are logarithmically increasing from start to end
        template <typename T, std::size_t N>
        std::array<T, N> logspace(T start, T end) {
            std::array<T, N> arr;
            T step = (end - start) / N;
            T val = start;
        
            for (std::size_t i = 0; i < N; ++i) {
                arr[i] = std::log(val);
                val += step;
            }
        
            return arr;
        }

        template <typename T>
        std::vector<T> linspace(T start, T end, std::size_t num_points) {
            std::vector<T> result;
            result.reserve(num_points);
            T step = (end - start) / num_points;
            T val = start;
        
            for (std::size_t i = 0; i < num_points; ++i) {
                result.push_back(val);
                val += step;
            }
        
            return result;
        }

        template <typename T>
        std::vector<T> logspace(T start, T end, std::size_t num_points) {
            if (start <= 0 || end <= 0) {
                throw std::invalid_argument("logspace requires positive start and end values.");
            }
            if (num_points < 2) {
                throw std::invalid_argument("logspace requires at least 2 points.");
            }
        
            std::vector<T> result;
            result.reserve(num_points);
        
            T log_start = std::log10(start);
            T log_end = std::log10(end);
            T step = (log_end - log_start) / (num_points - 1);
        
            for (std::size_t i = 0; i < num_points; ++i) {
                result.push_back(std::pow(10, log_start + i * step));
            }
        
            return result;
        }
    }
}