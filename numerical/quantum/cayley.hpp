class CayleySolver {
public:
    template <typename Func, typename M> M run(Func hamiltonian, M rho_0, double t, double h) {
        std::complex<double> j = {0.0, 1.0};
        std::complex<double> step = 0.5*j * h;
        M Ht = hamiltonian(t);
        M A = M::one() - Ht * step;
        M B = M::one() + Ht * step;
        
        return A;
    }
};