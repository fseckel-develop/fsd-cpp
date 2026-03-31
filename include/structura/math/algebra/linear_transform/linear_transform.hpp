// Created by Franz Seckel on 27.12.2025.
#pragma once
#include <structura/math/algebra/linear_transform/linear_transform_storage.hpp>
#include <structura/math/algebra/linear_transform/linear_transform_operations.hpp>
#include <structura/math/algebra/matrix.hpp>
#include <cassert>
#include <type_traits>


namespace structura::math::algebra {

    /// @brief N×N linear transform type (vector → vector).
    ///
    /// Represents a linear map in N-dimensional space.
    /// - Acts only on vectors
    /// - Composition via matrix multiplication
    /// - No translation (affine operations handled separately)
    ///
    /// @tparam valueType Scalar type (arithmetic)
    /// @tparam N Dimension of linear transform
    template <typename valueType, std::size_t N>
    struct LinearTransform :
        /// @brief Storage mixin holding the raw linear transform matrix data.
        detail::LinearTransformStorage<valueType, N>,

        /// @brief CRTP mixin providing linear operator operators and accessors.
        detail::LinearTransformOperations<LinearTransform<valueType,N>, valueType, N>
    {
        /// @brief Ensures the linear transform has a valid dimension.
        static_assert(N > 0, "Linear transform dimension must be greater than 0");

        /// @brief Ensures the linear transform element type is arithmetic.
        static_assert(std::is_arithmetic_v<valueType>, "Linear transform value type must be arithmetic");

        /// @brief Exposes the underlying row storage.
        /// This allows direct access to the row array for algorithms,
        /// interop, and low-level operations.
        using detail::LinearTransformStorage<valueType, N>::rows;

        /// Default constructor: identity
        constexpr LinearTransform() noexcept {
            for (std::size_t i = 0; i < N; ++i)
                for (std::size_t j = 0; j < N; ++j)
                    rows[i][j] = (i==j ? valueType(1) : valueType(0));
        }

        /// Construct from existing matrix
        explicit constexpr LinearTransform(const Matrix<valueType, N, N>& matrix) noexcept {
            for (std::size_t i = 0; i < N; ++i)
                rows[i] = matrix.rows[i];
        }
    };

} // namespace structura::math::algebra
