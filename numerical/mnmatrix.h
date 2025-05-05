#pragma once

#include <array>

namespace numerical {
    template <typename T, std::size_t M, std::size_t N>
    class MNMatrix {
    private:
        std::array<T, M * N> components{};

    public:
        MNMatrix() = default;
        MNMatrix(std::initializer_list<T> init);
        static MNMatrix zero();
        static MNMatrix one();

        T& operator()(std::size_t row, std::size_t col);
        const T& operator()(std::size_t row, std::size_t col) const;

        MNMatrix operator+(const MNMatrix& other) const;
        MNMatrix operator-(const MNMatrix& other) const;
        MNMatrix operator*(T scalar) const;
        template <std::size_t P> MNMatrix<T, M, P> operator*(const MNMatrix<T, N, P>& other) const;

        T norm();

        T trace() const;
        MNMatrix<T, N, M> trans() const;
        MNMatrix conj() const;
        MNMatrix<T, N, M> dag() const;
        std::size_t rows() const;
        std::size_t cols() const;
        std::size_t size() const;
        void display() const;
        void display_csv() const;
        void display_probabilities() const;

        MNMatrix commute(MNMatrix rhs);
        MNMatrix anticommute(MNMatrix rhs);
    };

    template <typename T, std::size_t M, std::size_t N> MNMatrix<T, M, N> operator*(T scalar, const MNMatrix<T, M, N>& matrix);
}

#include "mnmatrix.cpp"