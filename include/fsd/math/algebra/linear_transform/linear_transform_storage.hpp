// Created by Franz Seckel on 27.12.2025.
#pragma once
#include "../../algebra/matrix.hpp"

namespace fsd::math::algebra::detail
{
    /// @brief Storage type for a square linear transform.
    /// Reuses Matrix storage.
    template <typename valueType, std::size_t N>
    using LinearTransformStorage = Matrix<valueType, N, N>;

} // namespace fsd::math::algebra::detail
