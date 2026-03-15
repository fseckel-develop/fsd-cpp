// Created by Franz Seckel on 27.12.2025.
#pragma once
#include "../../algebra/matrix.hpp"

namespace fsd::math::algebra::detail
{
    /// @brief CRTP mixin providing linear transform operations.
    /// Supports:
    /// - Composition of transforms (operator*)
    /// - Application to vectors (operator*)
    ///
    /// @tparam DerivedLinearTransform Derived LinearTransform type (CRTP)
    /// @tparam valueType Scalar type
    /// @tparam N Dimension of linear transform
    template <typename DerivedLinearTransform, typename valueType, std::size_t N>
    struct LinearTransformOperations
    {
        /// @brief Compose two linear transforms.
        [[nodiscard]] constexpr DerivedLinearTransform
        operator*(const DerivedLinearTransform& other) const noexcept {
            const auto& self = static_cast<const DerivedLinearTransform&>(*this);
            DerivedLinearTransform result;
            for (std::size_t row = 0; row < N; ++row) {
                for (std::size_t columnJ = 0; columnJ < N; ++columnJ) {
                    valueType sum = valueType(0);
                    for (std::size_t columnK = 0; columnK < N; ++columnK)
                        sum += self.rows[row][columnK] * other.rows[columnK][columnJ];
                    result.rows[row][columnJ] = sum;
                }
            }
            return result;
        }

        /// @brief Apply transform to a vector.
        [[nodiscard]] constexpr Vector<valueType, N>
        operator*(const Vector<valueType, N>& vector) const noexcept {
            const auto& self = static_cast<const DerivedLinearTransform&>(*this);
            Vector<valueType, N> result{};
            for (std::size_t row = 0; row < N; ++row) {
                valueType sum = valueType(0);
                for (std::size_t column = 0; column < N; ++column)
                    sum += self.rows[row][column] * vector[column];
                result[row] = sum;
            }
            return result;
        }
    };

} // namespace fsd::math::algebra::detail
