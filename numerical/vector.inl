#include <array>
#include "vector.h"

template <typename T, std::size_t N>
NumericalVector<T, N>::NumericalVector(std::initializer_list<T> init) {
    std::size_t i = 0;
    for (auto val : init) {
        if (i < N) {
            components[i++] = val;
        }
    }
}

template <typename T, std::size_t N>
NumericalVector<T, N> NumericalVector<T, N>::clone() const {
    NumericalVector<T, N> new_vec;

    for (std::size_t i = 0; i < N; ++i) {
        new_vec[i] = (*this)[i];
    }

    return new_vec;
}

template <typename T, std::size_t N>
T& NumericalVector<T, N>::operator[](std::size_t index) {
    if (index >= N) {
        throw std::out_of_range("NumericalVector index out of bounds");
    }
    return components[index];
}

template <typename T, std::size_t N>
const T& NumericalVector<T, N>::operator[](std::size_t index) const {
    if (index >= N) {
        throw std::out_of_range("NumericalVector index out of bounds");
    }
    return components[index];
}

template <typename T, std::size_t N>
NumericalVector<T, N> NumericalVector<T, N>::operator+(const NumericalVector& other) const {
    NumericalVector result;
    for (std::size_t i = 0; i < N; ++i) {
        result[i] = components[i] + other[i];
    }
    return result;
}
    
template <typename T, std::size_t N>
NumericalVector<T, N> NumericalVector<T, N>::operator-(const NumericalVector& other) const {
    NumericalVector result;
    for (std::size_t i = 0; i < N; ++i) {
        result[i] = components[i] - other[i];
    }
    return result;
}

template <typename T, std::size_t N>
NumericalVector<T, N> NumericalVector<T, N>::operator*(T scalar) const {
    NumericalVector result;
    for (std::size_t i = 0; i < N; ++i) {
        result[i] = components[i] * scalar;
    }
    return result;
}

template <typename T, std::size_t N>
T NumericalVector<T, N>::dot(const NumericalVector& other) const {
    T result = T();
    for (std::size_t i = 0; i < N; ++i) {
        result += components[i] * other[i];
    }
    return result;
}

template <typename T, std::size_t N>
T NumericalVector<T, N>::magnitude() const {
    return std::sqrt(dot(*this));
}

template <typename T, std::size_t N>
NumericalVector<T, N> NumericalVector<T, N>::normalize() const {
    T mag = magnitude();
    if (mag == 0) {
        return *this;
    }
    return (*this) * (1 / mag);
}

template <typename T, std::size_t N>
std::size_t NumericalVector<T, N>::dim() const {
    return N;
}

template <typename T, std::size_t N>
void NumericalVector<T, N>::display() const {
    std::cout << "NumericalVector(";
    for (std::size_t i = 0; i < N; ++i) {
        std::cout << components[i] << (i < N - 1 ? ", " : "");
    }
    std::cout << ")\n";
}