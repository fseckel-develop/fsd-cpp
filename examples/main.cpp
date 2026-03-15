// Created by Franz Seckel on 17.12.2025.
#include <iostream>

#include "../include/fsd/core/binary_tree.hpp"
#include "../include/fsd/math/algebra/vector.hpp"
#include "../include/fsd/math/algebra/matrix.hpp"
#include "../include/fsd/math/geometry/point.hpp"

using namespace fsd::math::algebra;
using namespace fsd::math::geometry;

int main() {
    constexpr Vector3 translation = {1.0f, 2.0f, 3.0f};
    constexpr Vector3 rotationAxis = {0.0f, 1.0f, 0.0f};
    constexpr Vector3 scaleFactors = {3.0f, 4.0f, 0.5f};
    std::cout << "Translation:   " << translation << std::endl;
    std::cout << "Rotation axis: " << rotationAxis << std::endl;
    std::cout << "Scale along X: " << scaleFactors.x() << std::endl;
    std::cout << "Scale along Y: " << scaleFactors.y() << std::endl;
    std::cout << "Scale along Z: " << scaleFactors.z() << std::endl << std::endl;

    const auto matrix = translate(translation) * rotate(rotationAxis, 45.0);
    std::cout << "Matrix:\n" << matrix << std::endl << std::endl;

    constexpr Point3 pointA = {1.0f, 2.0f, 3.0f};
    constexpr Point3 pointB = {4.0f, 5.0f, 6.0f};
    constexpr auto vector = pointB - pointA;
    const auto pointC = pointB + vector;
    std::cout << "Point A:   " << pointA << std::endl;
    std::cout << "Point B:   " << pointB << std::endl;
    std::cout << "Vector AB: " << vector << std::endl;
    std::cout << "Point C:   " << pointC << std::endl;
}
