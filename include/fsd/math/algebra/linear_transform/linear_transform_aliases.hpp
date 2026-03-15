// Created by Franz Seckel on 27.12.2025.
#pragma once
#include "linear_transform.hpp"

namespace fsd::math::algebra
{
    using LinearTransform2 = LinearTransform<float,2>;
    using LinearTransform3 = LinearTransform<float,3>;
    using LinearTransform4 = LinearTransform<float,4>;

    using LinearTransform2d = LinearTransform<double,2>;
    using LinearTransform3d = LinearTransform<double,3>;
    using LinearTransform4d = LinearTransform<double,4>;

} // namespace fsd::math::algebra
