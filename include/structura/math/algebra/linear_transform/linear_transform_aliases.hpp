// Created by Franz Seckel on 27.12.2025.
#pragma once
#include <structura/math/algebra/linear_transform/linear_transform.hpp>


namespace structura::math::algebra {

    using LinearTransform2 = LinearTransform<float,2>;
    using LinearTransform3 = LinearTransform<float,3>;
    using LinearTransform4 = LinearTransform<float,4>;

    using LinearTransform2d = LinearTransform<double,2>;
    using LinearTransform3d = LinearTransform<double,3>;
    using LinearTransform4d = LinearTransform<double,4>;

} // namespace structura::math::algebra
