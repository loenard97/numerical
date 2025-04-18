#include <array>

namespace lib {
    namespace array {
        //! Array linspace
        //!
        //! Return an array where values are continuously increasing from start to end
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
    }
}