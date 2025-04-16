#pragma once

#include <array>

template <typename T, std::size_t N>
class NumericalVector {
private:
    std::array<T, N> components{};

public:
    NumericalVector() = default;
    NumericalVector(std::initializer_list<T> init);
    NumericalVector clone() const;

    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

    NumericalVector operator+(const NumericalVector& other) const;
    NumericalVector operator-(const NumericalVector& other) const;
    NumericalVector operator*(T scalar) const;

    T dot(const NumericalVector& other) const;
    T magnitude() const;
    NumericalVector normalize() const;
    std::size_t dim() const;
    void display() const;
};

#include "nvector.cpp"