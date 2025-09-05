// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUX_GVECTOR3D_HPP_INCLUDED
#define NUX_GVECTOR3D_HPP_INCLUDED

namespace nux {

template <
    typename T
>
class gvector3d {
public:
    // Types ------------------------------------------------------------------

    using value_type = T;

    // Public Data ------------------------------------------------------------

    value_type x;
    value_type y;
    value_type z;

    // Constructors and Destructor --------------------------------------------

    gvector3d ()
    noexcept = default;

    gvector3d (
        value_type initial_value
    )
    noexcept
        : x{initial_value}
        , y{initial_value}
        , z{initial_value}
    {
    } // function -------------------------------------------------------------

    gvector3d (
        value_type initial_x,
        value_type initial_y,
        value_type initial_z
    )
    noexcept
        : x{initial_x}
        , y{initial_y}
        , z{initial_z}
    {
    } // function -------------------------------------------------------------

    ~gvector3d ()
    = default;

    // Accessors --------------------------------------------------------------

    value_type*
    get_data_ptr ()
    noexcept
    {
        return &x;
    } // function -------------------------------------------------------------

    const value_type*
    get_data_ptr ()
    const noexcept
    {
        return &x;
    } // function -------------------------------------------------------------

    // Core -------------------------------------------------------------------

    value_type
    calculate_length ()
    const noexcept
    {
        return std::sqrt(x * x + y * y + z * z);
    } // function -------------------------------------------------------------

    void
    normalize ()
    noexcept
    {
        value_type length{calculate_length()};
        x /= length;
        y /= length;
        z /= length;
    } // function -------------------------------------------------------------

    // Operator Overloads -----------------------------------------------------

    friend
    gvector3d
    operator + (
        const gvector3d& left_operand,
        const gvector3d& right_operand
    )
    noexcept
    {
        return gvector3d{
            left_operand.x + right_operand.x,
            left_operand.y + right_operand.y,
            left_operand.z + right_operand.z
        };
    } // function -------------------------------------------------------------

    friend
    gvector3d
    operator - (
        const gvector3d& left_operand,
        const gvector3d& right_operand
    )
    noexcept
    {
        return gvector3d{
            left_operand.x - right_operand.x,
            left_operand.y - right_operand.y,
            left_operand.z - right_operand.z
        };
    } // function -------------------------------------------------------------

    friend
    gvector3d
    operator * (
        const gvector3d& left_operand,
        value_type right_operand
    ) {
        return gvector3d{
            left_operand.x * right_operand,
            left_operand.y * right_operand,
            left_operand.z * right_operand
        };
    } // function -------------------------------------------------------------

    friend
    gvector3d
    operator * (
        value_type left_operand,
        const gvector3d& right_operand
    ) {
        return gvector3d{
            left_operand * right_operand.x,
            left_operand * right_operand.y,
            left_operand * right_operand.z
        };
    } // function -------------------------------------------------------------
}; // class -------------------------------------------------------------------

template <
    typename T
>
T
distance_between (
    const gvector3d<T>& point1,
    const gvector3d<T>& point2
)
noexcept
{
    return (point2 - point1).calculate_length();
} // function -----------------------------------------------------------------

template <
    typename T
>
T
dot_product (
    const gvector3d<T>& point1,
    const gvector3d<T>& point2
)
noexcept
{
    return point1.x * point2.x + point1.y * point2.y + point1.z * point2.z;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif
