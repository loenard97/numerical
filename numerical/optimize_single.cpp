// optimization routines for one dimensional functions

#include <cstddef>
#include <cmath>

#include "util.h"
#include "constants.h"

namespace numerical {
	namespace optimize {
		template <typename T>
		struct OptimizeResult {
			T x;
			T fx;
			std::size_t iterations;
		};

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
		
		template <typename T, typename Func>
		OptimizeResult<T> brent(Func function, const T lower_bracket, const T upper_bracket, const T tolerance, std::size_t max_iterations) {
			T a = lower_bracket;
			T b = upper_bracket;
			T x, u, v, w;
			T fx, fu, fv, fw;
			T d, e;
			T xm, tol1, tol2;
			T r, q, p;
			std::size_t i;
		
			constexpr T phi = 0.5 * (3 - sqrt(5));
		
			x = w = v = a + phi * (b - a);
			fx = fw = fv = function(x);
			d = e = static_cast<T>(0);
		
			for (i = 0; i < max_iterations; ++i) {
				xm = 0.5 * (a + b);
				tol1 = tolerance * std::fabs(x) + 1e-10;
				tol2 = 2 * tol1;
		
				if (std::fabs(x - xm) <= (tol2 - 0.5 * (b - a))) {
					return OptimizeResult<T> { x, function(x), i };
				}
		
				if (std::fabs(e) > tol1) {
					// attempt parabola
					r = (x - w) * (fx - fv);
					q = (x - v) * (fx - fw);
					p = (x - v) * q - (x - w) * r;
					q = 2.0 * (q - r);
		
					if (q > 0.0) {
						p = -p;
					}
					q = std::fabs(q);
		
					// check if parabola is acceptable, 
					// fall back to golden section search if not
					if (
						std::fabs(p) < std::fabs(0.5 * q * e) 
						&& p > q * (a - x)
						&& p < q * (b - x)
					) {
						e = d;
						d = p / q;
					} else {
						if (x < xm) {
							e = b - x;
						} else {
							e = a - x;
						}
						d = phi * e;
					}
				} else {
					// fall back to golden section search
					if (x < xm) {
						e = b - x;
					} else {
						e = a - x;
					}
					d = phi * e;
				}
		
				// take a step, but never smaller than the tolerance
				if (std::fabs(d) >= tol1) {
					u = x + d;
				} else {
					u = x + numerical_util_sign(d) * tol1;
				}
				fu = function(u);
		
				if (fu <= fx) {
					if (u < x) {
						b = x;
					} else {
						a = x;
					}
					v = w;
					fv = fw;
					w = x;
					fw = fx;
					x = u;
					fx = fu;
				} else {
					if (u < x) {
						a = u;
					} else {
						b = u;
					}
					if (fu <= fw || w == x) {
						v = w;
						fv = fw;
						w = u;
						fw = fu;
					} else if (fu <= fv || v == x || v == w) {
						v = u;
						fv = fu;
					}
				}
			}
		
			return OptimizeResult<T> { x, function(x), i };
		}
	}
}