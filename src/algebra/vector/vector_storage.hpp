// Created by Franz Seckel on 19.12.2025.
#pragma once
#include <cstddef>

namespace fs::math::algebra::detail
{

#define FS_MATH_VEC_ACCESSOR(struct_name, component)        \
    constexpr valueType& component() noexcept               \
    { return storage.struct_name.component; }               \
    constexpr const valueType& component() const noexcept   \
    { return storage.struct_name.component; }

    /// @brief Generic fixed-size vector storage.
    ///
    /// Stores N scalar values in a contiguous array.
    /// This is the primary storage used for vectors with
    /// dimensions other than 2, 3, or 4.
    ///
    /// Design:
    /// - Trivially copyable
    /// - Standard layout
    /// - Contiguous memory suitable for SIMD and GPU upload
    ///
    /// @tparam valueType Scalar element type
    /// @tparam N Number of vector components
    template<typename valueType, std::size_t N>
    struct VectorStorage
    {
        union Storage {
            valueType data[N];  ///< Contiguous array of vector components.
            constexpr Storage() noexcept : data{} {}
        } storage;

        constexpr valueType* data() noexcept { return storage.data; }
        constexpr const valueType* data() const noexcept { return storage.data; }
    };

    /// @brief Specialized storage for 2D vectors.
    ///
    /// Provides named component access (`x`, `y`) and color aliases
    /// (`r`, `g`) while sharing the same underlying memory as `data`.
    ///
    /// Layout guarantee:
    /// - `x` aliases `data[0]`
    /// - `y` aliases `data[1]`
    ///
    /// @tparam valueType Scalar element type
    template<typename valueType>
    struct VectorStorage<valueType,2>
    {
        union Storage {
            struct XY { valueType x, y; } xy;   ///< Cartesian component access.
            struct RG { valueType r, g; } rg;   ///< Color component aliases.
            valueType data[2];                  ///< Contiguous array view.
            constexpr Storage() noexcept : data{} {}
        } storage;

        FS_MATH_VEC_ACCESSOR(xy, x)
        FS_MATH_VEC_ACCESSOR(xy, y)

        FS_MATH_VEC_ACCESSOR(rg, r)
        FS_MATH_VEC_ACCESSOR(rg, g)

        constexpr valueType* data_() noexcept { return storage.data; }
        constexpr const valueType* data_() const noexcept { return storage.data; }
    };

    /// @brief Specialized storage for 3D vectors.
    ///
    /// Provides named component access (`x`, `y`, `z`) and color aliases
    /// (`r`, `g`, `b`) while sharing the same underlying memory as `data`.
    ///
    /// Layout guarantee:
    /// - `x` aliases `data[0]`
    /// - `y` aliases `data[1]`
    /// - `z` aliases `data[2]`
    ///
    /// @tparam valueType Scalar element type
    template<typename valueType>
    struct VectorStorage<valueType,3>
    {
        union Storage {
            struct XYZ { valueType x, y, z; } xyz;  ///< Cartesian component access.
            struct RGB { valueType r, g, b; } rgb;  ///< Color component aliases.
            valueType data[3];                      ///< Contiguous array view.
            constexpr Storage() noexcept : data{} {}
        } storage;

        FS_MATH_VEC_ACCESSOR(xyz, x)
        FS_MATH_VEC_ACCESSOR(xyz, y)
        FS_MATH_VEC_ACCESSOR(xyz, z)

        FS_MATH_VEC_ACCESSOR(rgb, r)
        FS_MATH_VEC_ACCESSOR(rgb, g)
        FS_MATH_VEC_ACCESSOR(rgb, b)

        constexpr valueType* data() noexcept { return storage.data; }
        constexpr const valueType* data() const noexcept { return storage.data; }
    };

    /// @brief Specialized storage for 4D vectors.
    ///
    /// Provides named component access (`x`, `y`, `z`, `w`) and color
    /// aliases (`r`, `g`, `b`, `a`) while sharing the same underlying
    /// memory as `data`.
    ///
    /// Layout guarantee:
    /// - `x` aliases `data[0]`
    /// - `y` aliases `data[1]`
    /// - `z` aliases `data[2]`
    /// - `w` aliases `data[3]`
    ///
    /// @tparam valueType Scalar element type
    template<typename valueType>
    struct VectorStorage<valueType,4>
    {
        union Storage {
            struct XYZW { valueType x, y, z, w; } xyzw; ///< Cartesian component access.
            struct RGBA { valueType r, g, b, a; } rgba; ///< Color component aliases.
            valueType data[4];                          ///< Contiguous array view.
            constexpr Storage() noexcept : data{} {}
        } storage;

        FS_MATH_VEC_ACCESSOR(xyzw, x)
        FS_MATH_VEC_ACCESSOR(xyzw, y)
        FS_MATH_VEC_ACCESSOR(xyzw, z)
        FS_MATH_VEC_ACCESSOR(xyzw, w)

        FS_MATH_VEC_ACCESSOR(rgba, r)
        FS_MATH_VEC_ACCESSOR(rgba, g)
        FS_MATH_VEC_ACCESSOR(rgba, b)
        FS_MATH_VEC_ACCESSOR(rgba, a)

        constexpr valueType* data() noexcept { return storage.data; }
        constexpr const valueType* data() const noexcept { return storage.data; }
    };

#undef FS_MATH_VEC_ACCESSOR

} // namespace fs::math::algebra::detail
