// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUX_PAINT_HPP_INCLUDED
#define NUX_PAINT_HPP_INCLUDED

#include <vector>

#include <nux/gvector2d.hpp>
#include <nux/gvector4d.hpp>

namespace nux {

enum class paint_type {
    solid,
    linear_gradient,
    radial_gradient
}; // enum --------------------------------------------------------------------

class gradient_stop {
public:
    // Public Data ------------------------------------------------------------

    float position;
    gvector4d<float> color;

    // Constructors and Destructor --------------------------------------------

    gradient_stop (
        float initial_position,
        gvector4d<float> initial_color
    )
    noexcept
        : position{initial_position}
        , color{initial_color}
    {
    } // function -------------------------------------------------------------

    ~gradient_stop ()
    = default;

    // Copy Operations --------------------------------------------------------

    gradient_stop (
        const gradient_stop& other
    )
    = default;

    gradient_stop&
    operator = (
        const gradient_stop& other
    )
    = default;

    // Move Operations --------------------------------------------------------

    gradient_stop (
        gradient_stop&& other
    )
    noexcept = default;

    gradient_stop&
    operator = (
        gradient_stop&& other
    )
    noexcept = default;
}; // class -------------------------------------------------------------------

class paint {
public:
    // Public Data ------------------------------------------------------------

    paint_type type;
    gvector4d<float> color;
    std::vector<gradient_stop> gradient_stops;
    gvector2d<float> gradient_start;
    gvector2d<float> gradient_end;
    float global_opacity;

    // Constructors and Destructor --------------------------------------------

    paint ()
    = default;

    paint (
        paint_type initial_type,
        gvector4d<float> initial_color,
        const std::vector<gradient_stop>& initial_gradient_stops,
        gvector2d<float> initial_gradient_start,
        gvector2d<float> initial_gradient_end,
        float initial_global_opacity
    )
        : type{initial_type}
        , color{initial_color}
        , gradient_stops{initial_gradient_stops}
        , gradient_start{initial_gradient_start}
        , gradient_end{initial_gradient_end}
        , global_opacity{initial_global_opacity}
    {
    } // function -------------------------------------------------------------

    ~paint ()
    = default;

    // Copy Operations --------------------------------------------------------

    paint (
        const paint& other
    )
    = default;

    paint&
    operator = (
        const paint& other
    )
    = default;

    // Move Operations --------------------------------------------------------

    paint (
        paint&& other
    )
    noexcept = default;

    paint&
    operator = (
        paint&& other
    )
    noexcept = default;

    // Core -------------------------------------------------------------------

    static
    paint
    build_solid_color (
        const gvector4d<float>& color,
        float global_opacity = 1.0f
    ) {
        paint result;
        result.type = paint_type::solid;
        result.color = color;
        result.global_opacity = global_opacity;
        return result;
    } // function -------------------------------------------------------------

    static
    paint
    build_linear_gradient (
        const gvector2d<float>& start,
        const gvector2d<float>& end,
        const std::vector<gradient_stop>& stops,
        float global_opacity = 1.0f
    ) {
        paint result;
        result.type = paint_type::linear_gradient;
        result.gradient_start = start;
        result.gradient_end = end;
        result.gradient_stops = stops;
        result.global_opacity = global_opacity;
        return result;
    } // function -------------------------------------------------------------

    static
    paint
    build_radial_gradient (
        const gvector2d<float>& center,
        float radius,
        const std::vector<gradient_stop>& stops,
        float global_opacity = 1.0f
    ) {
        paint result;
        result.type = paint_type::radial_gradient;
        result.gradient_start = center;
        result.gradient_end = gvector2d<float>{radius, 0.0f};
        result.gradient_stops = stops;
        result.global_opacity = global_opacity;
        return result;
    } // function -------------------------------------------------------------
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif
