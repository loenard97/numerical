#include <iostream>
#include <complex>
#include <vector>
#include "../../eigen/Eigen/Dense"
#include "../../eigen/unsupported/Eigen/MatrixFunctions"

using Complex = std::complex<double>;
using Matrix = Eigen::Matrix2cd;

const Complex j = Complex(0, 1);
const Matrix SIGMA_X = (Matrix() << 0, 1, 1, 0).finished();
const Matrix SIGMA_Y = (Matrix() << 0, -j, j, 0).finished();
const Matrix SIGMA_Z = (Matrix() << 1, 0, 0, -1).finished();
const Matrix I = Matrix::Identity();

void print_rhos(std::vector<Matrix> ms) {
    double x, y, z;
    
    for (Matrix m : ms) {
        x = 2 * m(0, 1).real();
        y = 2 * m(0, 1).imag();
        z = m(1, 1).real() - m(0, 0).real();
        std::cout << x << ", " << y << ", " << z << "\n";
    }
}

class SolverExact {
public:
    bool dense_output = true;
    std::vector<Matrix> rhos;

    SolverExact() = default;

    void run(const double Omega[3], Matrix rho, double step, size_t n_steps) {
        Matrix H = 0.5 * Omega[0] * SIGMA_X + 0.5 * Omega[1] * SIGMA_Y + 0.5 * Omega[2] * SIGMA_Z;
        Matrix U = (j*step*H).exp();

        for (std::size_t i = 0; i < n_steps; ++i) {
            rho = U * rho * U.adjoint();

            if (dense_output)
                rhos.push_back(rho);
        }
    };
};

int main() {
    double Omega = 1.0;
    Matrix H = 0.5 * Omega * SIGMA_X;
    Matrix rho;
    rho << 1, 0, 0, 0;

    int n_steps = 100;
    double T = 2*3.14;
    double h = T / n_steps;
    Matrix U = (j*h*H).exp();
    std::vector<Matrix> rhos;

    for (std::size_t i = 0; i < n_steps; ++i) {
        rho = U * rho * U.adjoint();
        rhos.push_back(rho);
    }

    // std::cout << "H:\n" << H << "\n\n";
    // std::cout << "U:\n" << U << "\n\n";
    // std::cout << "rho:\n" << rho << "\n\n";

    print_rhos(rhos);

    return 0;
}