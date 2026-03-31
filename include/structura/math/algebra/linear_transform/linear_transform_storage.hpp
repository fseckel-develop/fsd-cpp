// Created by Franz Seckel on 27.12.2025.
#pragma once
#include <structura/math/algebra/matrix.hpp>


namespace structura::math::algebra::detail {

    /// @brief Storage type for a square linear transform.
    /// Reuses Matrix storage.
    template <typename valueType, std::size_t N>
    using LinearTransformStorage = Matrix<valueType, N, N>;

} // namespace structura::math::algebra::detail
