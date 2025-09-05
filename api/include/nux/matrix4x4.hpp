// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUX_MATRIX4X4_HPP_INCLUDED
#define NUX_MATRIX4X4_HPP_INCLUDED

#include <array>

namespace nux {

template <
    typename T
>
class matrix4x4 {
public:
    // Types ------------------------------------------------------------------

    using value_type = T;

    // Public Data ------------------------------------------------------------

    std::array<value_type, 16> elements;

    // Constructors and Destructor --------------------------------------------

    matrix4x4 ()
    noexcept = default;

    matrix4x4 (
        value_type diagonal_value
    )
    noexcept
    {
        for (
            std::size_t current_row{0};
            current_row < 4;
            ++current_row
        ) {
            for (
                std::size_t current_column{0};
                current_column < 4;
                ++current_column
            ) {
                if (current_row == current_column) {
                    operator()(current_row, current_column)
                        = diagonal_value;
                } else {
                    operator()(current_row, current_column)
                        = static_cast<value_type>(0);
                }
            }
        }
    } // function -------------------------------------------------------------

    ~matrix4x4 ()
    noexcept = default;

    // Accessors --------------------------------------------------------------

    value_type*
    get_data_ptr ()
    noexcept
    {
        return elements.data();
    } // function -------------------------------------------------------------

    const value_type*
    get_data_ptr ()
    const noexcept
    {
        return elements.data();
    } // function -------------------------------------------------------------

    // Core -------------------------------------------------------------------

    static
    matrix4x4
    build_orthographic (
        value_type width,
        value_type height
    ) {
        matrix4x4 result{1};
        result(0, 0) = static_cast<value_type>(2) / width;
        result(1, 1) = static_cast<value_type>(2) / (-height);
        result(2, 2) = -static_cast<value_type>(1);
        result(3, 0) = -1;
        result(3, 1) = 1;
        return result;
    } // function -------------------------------------------------------------

    // Operator Overloads -----------------------------------------------------

    value_type&
    operator () (
        std::size_t row,
        std::size_t column
    )
    noexcept
    {
        return elements[row * 4 + column];
    } // function -------------------------------------------------------------
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif
