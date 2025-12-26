// Created by Franz Seckel on 19.12.2025.
#pragma once
#include <ostream>
#include "vector_fwd.hpp"

namespace fs::math::algebra::detail
{
    /// @brief CRTP base providing arithmetic and element access operators for vectors.
    ///
    /// This class implements all fundamental vector operators that:
    /// - act element-wise
    /// - do not require higher-level algebraic meaning
    /// - can be constexpr-evaluated
    ///
    /// It assumes the derived type exposes a contiguous `data[]` array.
    ///
    /// @tparam DerivedVector Concrete vector type (CRTP)
    /// @tparam valueType Scalar element type
    /// @tparam N Vector dimension
    template<typename DerivedVector, typename valueType, std::size_t N>
    struct VectorOperations
    {
        /// @brief Mutable element access by index.
        /// @param index Component index
        constexpr valueType& operator[](std::size_t index) noexcept
        {
            return static_cast<DerivedVector*>(this)->data()[index];
        }

        /// @brief Immutable element access by index.
        /// @param index Component index
        constexpr const valueType& operator[](std::size_t index) const noexcept
        {
            return static_cast<const DerivedVector*>(this)->data()[index];
        }

        /// @brief Element-wise vector addition.
        constexpr DerivedVector& operator+=(const DerivedVector& other) noexcept
        {
            for (std::size_t i = 0; i < N; ++i)
                (*this)[i] += other[i];
            return static_cast<DerivedVector&>(*this);
        }

        /// @brief Element-wise vector subtraction.
        constexpr DerivedVector& operator-=(const DerivedVector& other) noexcept
        {
            for (std::size_t i = 0; i < N; ++i)
                (*this)[i] -= other[i];
            return static_cast<DerivedVector&>(*this);
        }

        /// @brief Scalar multiplication (in-place).
        constexpr DerivedVector& operator*=(valueType scalar) noexcept
        {
            for (std::size_t i = 0; i < N; ++i)
                (*this)[i] *= scalar;
            return static_cast<DerivedVector&>(*this);
        }

        /// @brief Scalar division (in-place).
        constexpr DerivedVector& operator/=(valueType scalar) noexcept
        {
            for (std::size_t i = 0; i < N; ++i)
                (*this)[i] /= scalar;
            return static_cast<DerivedVector&>(*this);
        }

        /// @brief Vector addition.
        [[nodiscard]] constexpr DerivedVector operator+(const DerivedVector& other) const noexcept
        {
            DerivedVector result = static_cast<const DerivedVector&>(*this);
            result += other;
            return result;
        }

        /// @brief Vector subtraction.
        [[nodiscard]] constexpr DerivedVector operator-(const DerivedVector& other) const noexcept
        {
            DerivedVector result = static_cast<const DerivedVector&>(*this);
            result -= other;
            return result;
        }

        /// @brief Scalar multiplication.
        [[nodiscard]] constexpr DerivedVector operator*(valueType scalar) const noexcept
        {
            DerivedVector result = static_cast<const DerivedVector&>(*this);
            result *= scalar;
            return result;
        }

        /// @brief Scalar division.
        [[nodiscard]] constexpr DerivedVector operator/(valueType scalar) const noexcept
        {
            DerivedVector result = static_cast<const DerivedVector&>(*this);
            result /= scalar;
            return result;
        }

        /// @brief Unary plus (identity).
        [[nodiscard]] constexpr DerivedVector operator+() const noexcept
        {
            return static_cast<const DerivedVector&>(*this);
        }

        /// @brief Unary negation.
        [[nodiscard]] constexpr DerivedVector operator-() const noexcept
        {
            DerivedVector result{};
            for (std::size_t i = 0; i < N; ++i)
                result[i] = -(*this)[i];
            return result;
        }

        /// @brief Equality comparison.
        [[nodiscard]] constexpr bool operator==(const DerivedVector& other) const noexcept
        {
            for (std::size_t i = 0; i < N; ++i)
                if ((*this)[i] != other[i])
                    return false;
            return true;
        }

        /// @brief Inequality comparison.
        [[nodiscard]] constexpr bool operator!=(const DerivedVector& other) const noexcept
        {
            return !(*this == other);
        }
    };

    /// @brief Scalar-left multiplication.
    /// @tparam valueType Scalar type
    /// @tparam N Vector dimension
    template<typename valueType, std::size_t N>
    [[nodiscard]] constexpr Vector<valueType, N>
    operator*(valueType scalar, const Vector<valueType, N>& vector) noexcept
    {
        return vector * scalar;
    }

    /// @brief Stream output operator for vectors.
    /// Prints the vector in the form: `(v0, v1, ..., vN)`
    /// @param outputStream Output stream
    /// @param vector Vector to print
    template<typename valueType, std::size_t N>
    std::ostream&
    operator<<(std::ostream& outputStream, const Vector<valueType, N>& vector)
    {
        outputStream << '(';
        for (std::size_t i = 0; i < N; ++i)
        {
            outputStream << vector[i];
            if (i + 1 < N) outputStream << ", ";
        }
        outputStream << ')';
        return outputStream;
    }

} // namespace fs::math::algebra::detail
