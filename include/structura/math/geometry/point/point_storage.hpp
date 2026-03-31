// Created by Franz Seckel on 26.12.2025.
#pragma once
#include <structura/math/algebra/vector/vector_storage.hpp>
#include <cstddef>


namespace structura::math::geometry::detail {

    /// @brief Storage type for fixed-size points.
    ///
    /// This alias defines the underlying storage used by point types.
    /// It currently maps directly to the vector storage implementation,
    /// providing:
    /// - Contiguous memory layout
    /// - Trivial copyability for arithmetic types
    /// - Standard layout suitable for SIMD and GPU interop
    ///
    /// The alias exists to preserve semantic separation between points
    /// and vectors while allowing storage reuse. The underlying storage
    /// may change in the future without affecting public point interfaces.
    ///
    /// @tparam valueType Scalar coordinate type
    /// @tparam N Point dimension
    template<typename valueType, std::size_t N>
    using PointStorage = algebra::detail::VectorStorage<valueType, N>;

} // namespace structura::math::geometry::detail
