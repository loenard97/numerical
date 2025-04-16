/*! \file matrix.h
    \brief A Documented file.
    
    Details.
*/

#pragma once

#include <iostream>
#include <array>
#include <cmath>
#include <tuple>
#include <stdexcept>
#include <complex>

template <typename T, std::size_t M, std::size_t N>
class NumericalMatrix {
private:
    std::array<T, M * N> components{};

public:
    NumericalMatrix() = default;
    NumericalMatrix(std::initializer_list<T> init);
    static NumericalMatrix zero();
    static NumericalMatrix one();

    T& operator()(std::size_t row, std::size_t col);
    const T& operator()(std::size_t row, std::size_t col) const;

    NumericalMatrix operator+(const NumericalMatrix& other) const;
    NumericalMatrix operator*(T scalar) const;
    template <std::size_t P> NumericalMatrix<T, M, P> operator*(const NumericalMatrix<T, N, P>& other) const;

    T norm();

    T trace() const;
    NumericalMatrix<T, N, M> trans() const;
    NumericalMatrix conj() const;
    NumericalMatrix<T, N, M> dag() const;
    std::size_t rows() const;
    std::size_t cols() const;
    void display() const;
    void display_probabilities() const;
};

#include "matrix.cpp"