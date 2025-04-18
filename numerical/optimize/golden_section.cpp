#include <cstddef>

#include "util.h"
#include "../constants.h"

namespace numerical {
	namespace optimize {
		template <typename T, typename Func>
		OptimizeResult<T> golden_section(Func function, const T lower_bracket, const T upper_bracket, const T tolerance, std::size_t max_iterations) {
			T a = lower_bracket;
			T b = upper_bracket;
			T c, d;
			std::size_t i;
		
			for (i = 0; i < max_iterations; ++i) {
				c = b - (b - a) / constants::phi;
				d = a + (b - a) / constants::phi;
				if (function(c) < function(d)) {
					b = d;
				} else {
					a = c;
				}

				if (std::fabs(b - a) > tolerance) {
					break;
				}
			}

			a = (b + a) / 2.0;
			b = function(a);

			return OptimizeResult<T> { a, b, i };
		}
    }
}