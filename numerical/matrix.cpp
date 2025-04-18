#include <cmath>
#include <tuple>
#include <stdexcept>
#include <complex>
#include <iostream>
#include <array>

#include "matrix.h"

namespace numerical {
    template <typename T, std::size_t M, std::size_t N>
    Matrix<T, M, N>::Matrix(std::initializer_list<T> init) {
        std::size_t i = 0;
        for (auto val : init) {
            if (i < N * M) {
                components[i++] = val;
            }
        }
    }

    template <typename T, std::size_t M, std::size_t N>
    Matrix<T, M, N> Matrix<T, M, N>::zero() {
        Matrix<T, N, M> mat;
        for (std::size_t i = 0; i < N; ++i) {
            for (std::size_t j = 0; j < M; ++j) {
                mat(i, j) = static_cast<T>(0);
            }
        }
        return mat;
    }

    template <typename T, std::size_t M, std::size_t N>
    Matrix<T, M, N> Matrix<T, M, N>::one() {
        Matrix<T, N, M> mat;
        for (std::size_t i = 0; i < N; ++i) {
            for (std::size_t j = 0; j < M; ++j) {
                if (i == j) {
                    mat(i, j) = static_cast<T>(1);
                } else {
                    mat(i, j) = static_cast<T>(0);
                }
            }
        }
        return mat;
    }

    template <typename T, std::size_t M, std::size_t N>
    T& Matrix<T, M, N>::operator()(std::size_t row, std::size_t col) {
        if (row >= M || col >= N) {
            throw std::out_of_range("NumericalMatrix index out of bounds");
        }
        
        return components[row * N + col];
    }

    template <typename T, std::size_t M, std::size_t N>
    const T& Matrix<T, M, N>::operator()(std::size_t row, std::size_t col) const {
        if (row >= M || col >= N) {
            throw std::out_of_range("NumericalMatrix index out of bounds");
        }

        return components[row * N + col];
    }

    template <typename T, std::size_t M, std::size_t N>
    Matrix<T, M, N> Matrix<T, M, N>::operator+(const Matrix& other) const {
        if ((*this).rows() != other.rows() ||(*this).cols() != other.cols()) {
            throw std::invalid_argument("NumericalMatrix dimensions are not valid");
        }

        Matrix result;
        for (std::size_t row = 0; row < M; ++row) {
            for (std::size_t col = 0; col < N; ++col) {
                result(row, col) = (*this)(row, col) + other(row, col);
            }
        }
        return result;
    }

    template <typename T, std::size_t M, std::size_t N>
    Matrix<T, M, N> Matrix<T, M, N>::operator*(T scalar) const {
        Matrix result;
        for (std::size_t row = 0; row < M; ++row) {
            for (std::size_t col = 0; col < N; ++col) {
                result(row, col) = (*this)(row, col) * scalar;
            }
        }
        return result;
    }

    template <typename T, std::size_t M, std::size_t N>
    template <std::size_t P>
    Matrix<T, M, P> Matrix<T, M, N>::operator*(const Matrix<T, N, P>& other) const {
        Matrix<T, M, P> result;
        for (std::size_t row = 0; row < M; ++row) {
            for (std::size_t col = 0; col < P; ++col) {
                result(row, col) = static_cast<T>(0);
                for (std::size_t k = 0; k < N; ++k) {
                    result(row, col) += (*this)(row, k) * other(k, col);
                }
            }
        }
        return result;
    }

    template <typename T, std::size_t M, std::size_t N>
    T Matrix<T, M, N>::norm() {
        T norm = static_cast<T>(0);
        for (std::size_t row = 0; row < M; ++row) {
            for (std::size_t col = 0; col < N; ++col) {
                norm += (*this)(row, col) * (*this)(row, col);
            }
        }
        return std::sqrt(norm);
    }

    template <typename T, std::size_t M, std::size_t N>
    T Matrix<T, M, N>::trace() const {
        if (M != N) {
            throw std::invalid_argument("Trace not defined for M != N matrices");
        }

        T trace = static_cast<T>(0);
        for (std::size_t i = 0; i < N; ++i) {
            trace += (*this)(i, i);
        }
        return trace;
    }

    template <typename T, std::size_t M, std::size_t N>
    Matrix<T, N, M> Matrix<T, M, N>::trans() const {
        Matrix<T, N, M> result;
        for (std::size_t row = 0; row < M; ++row) {
            for (std::size_t col = 0; col < N; ++col) {
                result(col, row) = (*this)(row, col);
            }
        }
        return result;
    }

    template <typename T, std::size_t M, std::size_t N>
    Matrix<T, M, N> Matrix<T, M, N>::conj() const {
        Matrix result;
        for (std::size_t row = 0; row < M; ++row) {
            for (std::size_t col = 0; col < N; ++col) {
                result(row, col) = std::conj((*this)(row, col));
            }
        }
        return result;
    }

    template <typename T, std::size_t M, std::size_t N>
    Matrix<T, N, M> Matrix<T, M, N>::dag() const {
        return (*this).conj().trans();
    }

    template <typename T, std::size_t M, std::size_t N>
    std::size_t Matrix<T, M, N>::rows() const {
        return M;
    }

    template <typename T, std::size_t M, std::size_t N>
    std::size_t Matrix<T, M, N>::cols() const {
        return N;
    }

    template <typename T, std::size_t M, std::size_t N>
    void Matrix<T, M, N>::display() const {
        std::cout << "NumericalMatrix<" << (*this).rows() << "x" << (*this).cols() << ">(\n";
        for (std::size_t row = 0; row < M; ++row) {
            std::cout << "  ";
            for (std::size_t col = 0; col < N; ++col) {
                std::cout << (*this)(row, col) << ", ";
            }
            std::cout << "\n";
        }
        std::cout << ")\n";
    }

    template <typename T, std::size_t M, std::size_t N>
    void Matrix<T, M, N>::display_probabilities() const {
        for (std::size_t i = 0; i < M * N; ++i) {
            std::cout << std::abs(components[i] * std::conj(components[i])) << ((i + 1 < M * N) ? ", " : " ");
        }
        std::cout << "\n";
    }
}