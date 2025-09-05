// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUX_GVECTOR2D_HPP_INCLUDED
#define NUX_GVECTOR2D_HPP_INCLUDED

namespace nux {

template <
    typename T
>
class gvector2d {
public:
    // Types ------------------------------------------------------------------

    using value_type = T;

    // Public Data ------------------------------------------------------------

    value_type x;
    value_type y;

    // Constructors and Destructor --------------------------------------------

    gvector2d ()
    noexcept = default;

    gvector2d (
        value_type initial_value
    )
    noexcept
        : x{initial_value}
        , y{initial_value}
    {
    } // function -------------------------------------------------------------

    gvector2d (
        value_type initial_x,
        value_type initial_y
    )
    noexcept
        : x{initial_x}
        , y{initial_y}
    {
    } // function -------------------------------------------------------------

    ~gvector2d ()
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
        return std::sqrt(x * x + y * y);
    } // function -------------------------------------------------------------

    void
    normalize ()
    noexcept
    {
        value_type length{calculate_length()};
        x /= length;
        y /= length;
    } // function -------------------------------------------------------------

    // Operator Overloads -----------------------------------------------------

    friend
    gvector2d
    operator + (
        const gvector2d& left_operand,
        const gvector2d& right_operand
    )
    noexcept
    {
        return gvector2d{
            left_operand.x + right_operand.x,
            left_operand.y + right_operand.y
        };
    } // function -------------------------------------------------------------

    friend
    gvector2d
    operator - (
        const gvector2d& left_operand,
        const gvector2d& right_operand
    )
    noexcept
    {
        return gvector2d{
            left_operand.x - right_operand.x,
            left_operand.y - right_operand.y
        };
    } // function -------------------------------------------------------------

    friend
    gvector2d
    operator * (
        const gvector2d& left_operand,
        value_type right_operand
    ) {
        return gvector2d{
            left_operand.x * right_operand,
            left_operand.y * right_operand
        };
    } // function -------------------------------------------------------------

    friend
    gvector2d
    operator * (
        value_type left_operand,
        const gvector2d& right_operand
    ) {
        return gvector2d{
            left_operand * right_operand.x,
            left_operand * right_operand.y
        };
    } // function -------------------------------------------------------------
}; // class -------------------------------------------------------------------

template <
    typename T
>
T
distance_between (
    const gvector2d<T>& point1,
    const gvector2d<T>& point2
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
    const gvector2d<T>& point1,
    const gvector2d<T>& point2
)
noexcept
{
    return point1.x * point2.x + point1.y * point2.y;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif
