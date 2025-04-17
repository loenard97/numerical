/*! \file matrix.h
    \brief A Documented file.
    
    Details.
*/

#pragma once

#include <array>

namespace numerical {
    template <typename T, std::size_t M, std::size_t N>
    class Matrix {
    private:
        std::array<T, M * N> components{};

    public:
        Matrix() = default;
        Matrix(std::initializer_list<T> init);
        static Matrix zero();
        static Matrix one();

        T& operator()(std::size_t row, std::size_t col);
        const T& operator()(std::size_t row, std::size_t col) const;

        Matrix operator+(const Matrix& other) const;
        Matrix operator*(T scalar) const;
        template <std::size_t P> Matrix<T, M, P> operator*(const Matrix<T, N, P>& other) const;

        T norm();

        T trace() const;
        Matrix<T, N, M> trans() const;
        Matrix conj() const;
        Matrix<T, N, M> dag() const;
        std::size_t rows() const;
        std::size_t cols() const;
        void display() const;
        void display_probabilities() const;
    };
}

#include "matrix.cpp"