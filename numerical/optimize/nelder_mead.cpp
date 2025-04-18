#include <vector>

#include "../nvector.h"
#include "../sort/sort.h"

namespace numerical {
    namespace optimize {
        template <typename T, typename Func, std::size_t N>
        NVector<T, N> nelder_mead(Func function, const NVector<T, N> p0, const std::size_t max_iterations) {
            float alpha = 1.0;
            float gamma = 2.0;
            float rho = 0.5;
            float sigma = 0.5;
        
            std::size_t i;
            std::size_t iter = 0;
            T fr, fe, fc;
            NVector<T, N> x0, xr, xe, xc;
            std::vector<NVector<T, N>> simplex = {p0};
            std::vector<T> fsimplex;
        
            // starting simplex
            for (i = 0; i < N; ++i) {
                x0 = p0.clone();
                x0[i] += 1.0;
                simplex.push_back(x0);
            }
        
            while (iter < max_iterations) {
                iter += 1;
        
                // evaluate function at each simplex point
                fsimplex.clear();
                for (const auto& val : simplex) {
                    fsimplex.push_back(function(val));
                }
                sort::cosort_vector_insertion(fsimplex, simplex);
        
                // compute centoid
                for (i = 0; i < N; ++i) {
                    x0[i] = static_cast<T>(0);
                }
                for (i = 0; i < N + 1; ++i) {
                    x0 = x0 + simplex.at(i);
                }
                x0 = x0 * (1.0 / (T) N);
        
                // reflect
                xr = x0 + (x0 - simplex.at(N)) * alpha;
                fr = function(xr);
                if (fsimplex.at(0) <= fr && fr <= fsimplex.at(N - 1)) {
                    simplex.at(N) = xr;
                    continue;
                } 
        
                // expand
                if (fr < fsimplex.at(0)) {
                    xe = x0 + (xr - x0) * gamma;
                    fe = function(xe);
                    if (fe < fr) {
                        simplex.at(N) = xe;
                    } else {
                        simplex.at(N) = xr;
                    }
                    continue;
                }
        
                // contract
                if (fr < fsimplex.at(N)) {
                    // contract outside
                    xc = x0 + (xr - x0) * rho;
                    fc = function(xc);
                    if (fc < fr) {
                        simplex.at(N) = xc;
                        continue;
                    }
                } else {
                    // contract inside
                    xc = x0 + (simplex.at(N) - x0) * rho;
                    fc = function(xc);
                    if (fc < fsimplex.at(N)) {
                        simplex.at(N) = xc;
                        continue;
                    }
                }
        
                // shrink
                for (i = 0; i < N + 1; ++i) {
                    simplex.at(i) = simplex.at(i) * sigma;
                }
            }
        
            // return centoid when done
            for (i = 0; i < N; ++i) {
                x0[i] = static_cast<T>(0);
            }
            for (i = 0; i < N + 1; ++i) {
                x0 = x0 + simplex.at(i);
            }
            x0 = x0 * (1.0 / (T) N);
        
            return x0;
        }
    }
}