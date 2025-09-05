// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/paint.h>
#include "handles.hpp"

NUXC_EXTERNC
nux_gradient_stop_t*
nux_gradient_stop_create (
    float position,
    nux_gvector4d_t* color
) {
    return new nux_gradient_stop_t{
        nux::gradient_stop{position, *nux_impl_map(color)}
    };
}

NUXC_EXTERNC
void
nux_gradient_stop_destroy (
    nux_gradient_stop_t* gradient_stop
) {
    delete gradient_stop;
}

NUXC_EXTERNC
void
nux_paint_destroy (
    nux_paint_t* paint
) {
    delete paint;
}

NUXC_EXTERNC
nux_paint_t*
nux_paint_build_solid_color (
    nux_gvector4d_t* color,
    float global_opacity
) {
    return new nux_paint_t{
        nux::paint::build_solid_color(*nux_impl_map(color), global_opacity)
    };
}

NUXC_EXTERNC
nux_paint_t*
nux_paint_build_linear_gradient (
    nux_gvector2d_t* start,
    nux_gvector2d_t* end,
    nux_gradient_stop_t** stops,
    int stop_count,
    float global_opacity
) {
    return new nux_paint_t{
        nux::paint::build_linear_gradient(
            *nux_impl_map(start),
            *nux_impl_map(end),
            nux_impl_map<nux::gradient_stop>(stops, stop_count),
            global_opacity
        )
    };
}

NUXC_EXTERNC
nux_paint_t*
nux_paint_build_radial_gradient (
    nux_gvector2d_t* center,
    float radius,
    nux_gradient_stop_t** stops,
    int stop_count,
    float global_opacity
) {
    return new nux_paint_t{
        nux::paint::build_radial_gradient(
            *nux_impl_map(center),
            radius,
            nux_impl_map<nux::gradient_stop>(stops, stop_count),
            global_opacity
        )
    };
}
