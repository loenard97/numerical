#include <array>
#include <iostream>

#include "nvector.h"

namespace numerical {
    template <typename T, std::size_t N>
    NVector<T, N>::NVector(std::initializer_list<T> init) {
        std::size_t i = 0;
        for (auto val : init) {
            if (i < N) {
                components[i++] = val;
            }
        }
    }

    template <typename T, std::size_t N>
    NVector<T, N> NVector<T, N>::clone() const {
        NVector<T, N> new_vec;

        for (std::size_t i = 0; i < N; ++i) {
            new_vec[i] = (*this)[i];
        }

        return new_vec;
    }

    template <typename T, std::size_t N>
    NVector<T, N> NVector<T, N>::zero() {
        NVector<T, N> new_vec;

        for (std::size_t i = 0; i < N; ++i) {
            new_vec[i] = static_cast<T>(0);
        }

        return new_vec;
    }

    template <typename T, std::size_t N>
    T& NVector<T, N>::operator[](std::size_t index) {
        if (index >= N) {
            throw std::out_of_range("NVector index out of bounds");
        }
        return components[index];
    }

    template <typename T, std::size_t N>
    const T& NVector<T, N>::operator[](std::size_t index) const {
        if (index >= N) {
            throw std::out_of_range("NumericalVector index out of bounds");
        }
        return components[index];
    }

    template <typename T, std::size_t N>
    NVector<T, N> NVector<T, N>::operator+(const NVector& other) const {
        NVector result;
        for (std::size_t i = 0; i < N; ++i) {
            result[i] = components[i] + other[i];
        }
        return result;
    }
        
    template <typename T, std::size_t N>
    NVector<T, N> NVector<T, N>::operator-(const NVector& other) const {
        NVector result;
        for (std::size_t i = 0; i < N; ++i) {
            result[i] = components[i] - other[i];
        }
        return result;
    }

    template <typename T, std::size_t N>
    NVector<T, N> NVector<T, N>::operator*(T scalar) const {
        NVector result;
        for (std::size_t i = 0; i < N; ++i) {
            result[i] = components[i] * scalar;
        }
        return result;
    }

    template <typename T, std::size_t N>
    T NVector<T, N>::dot(const NVector& other) const {
        T result = T();
        for (std::size_t i = 0; i < N; ++i) {
            result += components[i] * other[i];
        }
        return result;
    }

    template <typename T, std::size_t N>
    T NVector<T, N>::magnitude() const {
        return std::sqrt(dot(*this));
    }

    template <typename T, std::size_t N>
    NVector<T, N> NVector<T, N>::normalize() const {
        T mag = magnitude();
        if (mag == 0) {
            return *this;
        }
        return (*this) * (1 / mag);
    }

    template <typename T, std::size_t N>
    std::size_t NVector<T, N>::dim() const {
        return N;
    }

    template <typename T, std::size_t N>
    void NVector<T, N>::display() const {
        std::cout << "NVector(";
        for (std::size_t i = 0; i < N; ++i) {
            std::cout << components[i] << (i < N - 1 ? ", " : "");
        }
        std::cout << ")\n";
    }
}