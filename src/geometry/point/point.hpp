// Created by Franz Seckel on 26.12.2025.
#pragma once
#include <cassert>
#include <type_traits>
#include <initializer_list>
#include "point_storage.hpp"
#include "point_operations.hpp"

namespace fs::math::geometry
{
    /// @brief Fixed-size affine point type.
    ///
    /// Represents a point in an N-dimensional affine space.
    ///
    /// A point models a location, not a direction, and therefore does
    /// not form a vector space. Only affine-valid operations are provided:
    /// - Translation by a vector (`Point + Vector`, `Point - Vector`)
    /// - Displacement between points (`Point - Point -> Vector`)
    ///
    /// Unsupported operations (by design) include:
    /// - Point + Point
    /// - Scalar multiplication or division
    /// - Unary negation
    ///
    /// Design properties:
    /// - Fixed size known at compile time
    /// - Contiguous memory layout
    /// - Trivially copyable for arithmetic types
    /// - Standard layout and SIMD-friendly
    /// - Zero runtime overhead abstractions
    ///
    /// Storage:
    /// - Uses `detail::PointStorage`, currently backed by vector storage
    ///
    /// Operations:
    /// - Affine operators provided via `detail::PointOperations` (CRTP)
    ///
    /// @tparam valueType Scalar coordinate type (must be arithmetic)
    /// @tparam N Point dimension (must be > 0)
    template<typename valueType, std::size_t N>
    struct Point :
        /// @brief Storage mixin holding the raw point coordinates.
        detail::PointStorage<valueType, N>,

        /// @brief CRTP mixin providing affine point operations.
        detail::PointOperations<Point<valueType, N>, valueType, N>
    {
        /// @brief Ensures the point coordinate type is arithmetic.
        static_assert(std::is_arithmetic_v<valueType>, "Point value type must be arithmetic");

        /// @brief Ensures the point has at least one dimension.
        static_assert(N > 0, "Point size must be greater than 0");

        /// @brief Exposes the underlying contiguous coordinate data.
        using detail::PointStorage<valueType, N>::data;

        /// @brief Default constructor.
        constexpr Point() noexcept = default;

        /// @brief Construct a point from a list of N coordinate values.
        /// @param list Initializer list containing exactly N values
        constexpr Point(std::initializer_list<valueType> list) noexcept
        {
            assert(list.size() == N && "Point initializer list size mismatch");
            std::size_t i = 0;
            for (auto value : list)
                data()[i++] = value;
        }

        /// @brief Implicit conversion from array (optional)
        explicit constexpr Point(const valueType (&array)[N]) noexcept
        {
            for (std::size_t index = 0; index < N; ++index)
                data[index] = array[index];
        }
    };

} // namespace fs::math::geometry
