#pragma once

#include <array>

namespace numerical {
    template <typename T, std::size_t N>
    class NVector {
    private:
        std::array<T, N> components{};

    public:
        NVector() = default;
        NVector(std::initializer_list<T> init);
        NVector clone() const;

        T& operator[](std::size_t index);
        const T& operator[](std::size_t index) const;

        NVector operator+(const NVector& other) const;
        NVector operator-(const NVector& other) const;
        NVector operator*(T scalar) const;

        T dot(const NVector& other) const;
        T magnitude() const;
        NVector normalize() const;
        std::size_t dim() const;
        void display() const;
    };
}

#include "nvector.cpp"