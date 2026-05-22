#include "../mnmatrix.h"

namespace numerical {
    namespace quantum {
        template <typename Func>
        class CayleySolver {
            Func hamiltonian;
            MNMatrix<double, 2, 2>::MNMatrix rho_0;
        
        public:
            CayleySolver() {};

        private:
            double propagator(double t, double h) {
                return hamiltonian(t);
            }
        };
    }
}