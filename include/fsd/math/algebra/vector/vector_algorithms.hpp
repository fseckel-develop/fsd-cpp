// Created by Franz Seckel on 19.12.2025.
#pragma once
#include <cmath>
#include <fsd/math/algebra/vector/vector_fwd.hpp>

namespace fsd::math::algebra
{
    /// @brief Computes the dot product of two vectors.
    template<typename valueType, std::size_t N>
    [[nodiscard]] constexpr valueType
    dot(const Vector<valueType, N>& first, const Vector<valueType, N>& second) noexcept
    {
        valueType result{};
        for (std::size_t i = 0; i < N; ++i)
            result += first.data()[i] * second.data()[i];
        return result;
    }

    /// @brief Computes the squared length (magnitude) of a vector.
    /// This avoids the costly square root operation and is suitable
    /// for distance comparisons.
    template<typename valueType, std::size_t N>
    [[nodiscard]] constexpr valueType
    lengthSquared(const Vector<valueType, N>& vector) noexcept
    {
        return dot(vector, vector);
    }

    /// @brief Computes the Euclidean length (magnitude) of a vector.
    template<typename valueType, std::size_t N>
    [[nodiscard]] valueType
    length(const Vector<valueType, N>& vector) noexcept
    {
        return static_cast<valueType>(std::sqrt(lengthSquared(vector)));
    }

    /// @brief Returns a normalized (unit-length) copy of a vector.
    /// If the vector has zero length, a zero vector is returned.
    template<typename valueType, std::size_t N>
    [[nodiscard]] Vector<valueType, N>
    normalize(const Vector<valueType, N>& vector) noexcept
    {
        valueType vectorLength = length(vector);
        return vectorLength > valueType{}
            ? vector / vectorLength
            : Vector<valueType, N>{};
    }

    /// @brief Computes the cross product of two 3D vectors.
    /// The cross product produces a vector perpendicular to the
    /// plane spanned by the inputs, following the right-hand rule.
    /// @param first First 3D vector
    /// @param second Second 3D vector
    template<typename valueType>
    [[nodiscard]] constexpr Vector<valueType, 3>
    cross(const Vector<valueType, 3>& first, const Vector<valueType, 3>& second) noexcept
    {
        return {
            first.y() * second.z() - first.z() * second.y(),
            first.z() * second.x() - first.x() * second.z(),
            first.x() * second.y() - first.y() * second.x()
        };
    }
} // namespace fsd::math::algebra
