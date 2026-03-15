// Created by Franz Seckel on 18.12.2025.
#pragma once
#include <cassert>
#include <type_traits>
#include <initializer_list>
#include <fsd/math/algebra/vector/vector_storage.hpp>
#include <fsd/math/algebra/vector/vector_operations.hpp>

namespace fsd::math::algebra
{
    /// @brief Fixed-size mathematical vector type.
    ///
    /// Represents a vector of `N` scalar elements with a compile-time
    /// dimension. The vector provides named component access for
    /// common dimensions (2D–4D), contiguous memory layout, and
    /// arithmetic operators via CRTP.
    ///
    /// Design properties:
    /// - Fixed size known at compile time
    /// - Contiguous memory layout (`data[N]`)
    /// - Trivially copyable for arithmetic types
    /// - Standard layout and SIMD-friendly
    /// - No virtual functions or heap allocation
    ///
    /// Storage:
    /// - Elements stored in `detail::VectorStorage`
    /// - Named access (`x,y,z,w` and `r,g,b,a`) for N ≤ 4
    ///
    /// Operations:
    /// - Arithmetic and indexing provided by `VectorOperations`
    /// - Mathematical meaning provided by free algorithms
    ///
    /// @tparam valueType Scalar element type (must be arithmetic)
    /// @tparam N Vector dimension (must be > 0)
    template<typename valueType, std::size_t N>
    struct Vector :
        /// @brief Storage mixin holding the raw vector data.
        detail::VectorStorage<valueType, N>,

        /// @brief CRTP mixin providing vector operators.
        detail::VectorOperations<Vector<valueType, N>, valueType, N>
    {
        /// @brief Ensures the vector element type is arithmetic.
        static_assert(std::is_arithmetic_v<valueType>, "Vector value type must be arithmetic");

        /// @brief Ensures the vector has at least one element.
        static_assert(N > 0, "Vector size must be greater than 0");

        /// @brief Exposes the underlying contiguous data array.
        /// This allows direct indexed access, interoperability with
        /// APIs expecting raw pointers, and use in generic algorithms.
        using detail::VectorStorage<valueType, N>::data;

        /// Default constructor
        constexpr Vector() noexcept = default;

        /// @brief Constructor from a list of N elements.
        /// @param list List of exactly N elements
        constexpr Vector(std::initializer_list<valueType> list) noexcept
        {
            assert(list.size() == N && "Vector initializer list size mismatch");
            std::size_t i = 0;
            for (const auto& value : list)
                data()[i++] = value;
        }

        /// @brief Implicit conversion from array (optional)
        explicit constexpr Vector(const valueType (&array)[N]) noexcept
        {
            for (std::size_t index = 0; index < N; ++index)
                data[index] = array[index];
        }
    };
} // namespace fsd::math::algebra
