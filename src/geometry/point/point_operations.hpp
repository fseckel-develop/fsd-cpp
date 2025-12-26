// Created by Franz Seckel on 26.12.2025.
#pragma once
#include <ostream>
#include "point_fwd.hpp"
#include "algebra/vector/vector_fwd.hpp"

namespace fs::math::geometry::detail
{
    /// @brief CRTP mixin providing affine operations for points.
    ///
    /// This mixin defines the valid affine operations for a point type:
    /// - Translation by a vector
    ///
    /// It intentionally does NOT provide:
    /// - Point + Point
    /// - Scalar multiplication or division
    /// - Unary negation
    ///
    /// This enforces affine-space semantics at compile time.
    ///
    /// @tparam DerivedPoint Concrete point type (CRTP)
    /// @tparam valueType Scalar coordinate type
    /// @tparam N Point dimension
    template<typename DerivedPoint, typename valueType, std::size_t N>
    struct PointOperations
    {
        /// @brief Translate a point by a vector.
        /// @param vector Translation vector
        /// @return Translated point
        [[nodiscard]] constexpr DerivedPoint
        operator+(const algebra::Vector<valueType, N>& vector) const noexcept
        {
            const auto& self = static_cast<const DerivedPoint&>(*this);
            DerivedPoint result;
            for (std::size_t i = 0; i < N; ++i)
                result.data()[i] = self.data()[i] + vector.data()[i];
            return result;
        }

        /// @brief Translate a point by the negation of a vector.
        /// @param vector Translation vector
        /// @return Translated point
        [[nodiscard]] constexpr DerivedPoint
        operator-(const algebra::Vector<valueType, N>& vector) const noexcept
        {
            const auto& self = static_cast<const DerivedPoint&>(*this);
            DerivedPoint result;
            for (std::size_t i = 0; i < N; ++i)
                result.data()[i] = self.data()[i] - vector.data()[i];
            return result;
        }
    };

    /// @brief Compute the displacement vector between two points.
    /// Subtracting two points yields the vector that transforms the
    /// second point into the first.
    /// @param first Minuend point
    /// @param second Subtrahend point
    /// @return Displacement vector between the two points
    template<typename valueType, std::size_t N>
    [[nodiscard]] constexpr algebra::Vector<valueType, N>
    operator-(const Point<valueType, N>& first, const Point<valueType, N>& second) noexcept
    {
        algebra::Vector<valueType, N> result;
        for (std::size_t i = 0; i < N; ++i)
            result.data()[i] = first.data()[i] - second.data()[i];
        return result;
    }

    /// @brief Stream output operator for points.
    /// Prints the vector in the form: `(p0, p1, ..., pN)`
    /// @param outputStream Output stream
    /// @param point Point to print
    template<typename valueType, std::size_t N>
    std::ostream&
    operator<<(std::ostream& outputStream, const Point<valueType, N>& point)
    {
        outputStream << '(';
        for (std::size_t i = 0; i < N; ++i)
        {
            outputStream << point.data()[i];
            if (i + 1 < N) outputStream << ", ";
        }
        outputStream << ')';
        return outputStream;
    }

} // namespace fs::math::geometry::detail