// optimization routines for one dimensional functions
#include <cstddef>
#include "util.h"
#include "constants.h"

template <typename T, typename Func>
T numerical_optimize_golden_section(Func f, T lower_bracket, T upper_bracket, T tolerance) {
    T a, b, c, d;
    a = lower_bracket;
    b = upper_bracket;

    while (NUMERICAL_UTIL_ABS(b - a) > tolerance) {
        c = b - (b - a) / NUMERICAL_CONSTANTS_PHI;
        d = a + (b - a) / NUMERICAL_CONSTANTS_PHI;
        if (f(c) < f(d)) {
            b = d;
        } else {
            a = c;
        }
    }

    return (b + a) / 2.0;
}

template <typename T>
T numerical_optimize_brent(T a, T b, T f(const T), const T tol, const std::size_t max_iter) {
	T x, u, v, w;
	T fx, fu, fv, fw;
	T d, e;
	T xm, tol1, tol2;
	T r, q, p;

	constexpr T phi = 0.5 * (3 - sqrt(5));

	x = w = v = a + phi * (b - a);
	fx = fw = fv = f(x);
	d = e = static_cast<T>(0);

	for (std::size_t i = 0; i < max_iter; ++i) {
		xm = 0.5 * (a + b);
		tol1 = tol * numerical_util_abs(x) + 1e-10;
		tol2 = 2 * tol1;

		if (numerical_util_abs(x - xm) <= (tol2 - 0.5 * (b - a))) {
			return x;
		}

		if (numerical_util_abs(e) > tol1) {
			// attempt parabola
			r = (x - w) * (fx - fv);
			q = (x - v) * (fx - fw);
			p = (x - v) * q - (x - w) * r;
			q = 2.0 * (q - r);

			if (q > 0.0) {
				p = -p;
			}
			q = numerical_util_abs(q);

			// check if parabola is acceptable, 
			// fall back to golden section search if not
			if (
				numerical_util_abs(p) < numerical_util_abs(0.5 * q * e) 
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
		if (numerical_util_abs(d) >= tol1) {
			u = x + d;
		} else {
			u = x + numerical_util_sign(d) * tol1;
		}
		fu = f(u);

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

	return x;
}