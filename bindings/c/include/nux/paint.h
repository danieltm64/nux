// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUXC_PAINT_H_INCLUDED
#define NUXC_PAINT_H_INCLUDED

#include <nux/gvector2d.h>
#include <nux/gvector4d.h>

typedef struct nux_gradient_stop_t nux_gradient_stop_t;

NUXC_CONDITIONAL_EXPORT
nux_gradient_stop_t*
nux_gradient_stop_create (
    float position,
    nux_gvector4d_t* color
);

NUXC_CONDITIONAL_EXPORT
void
nux_gradient_stop_destroy (
    nux_gradient_stop_t* gradient_stop
);

typedef struct nux_paint_t nux_paint_t;

NUXC_CONDITIONAL_EXPORT
void
nux_paint_destroy (
    nux_paint_t* paint
);

NUXC_CONDITIONAL_EXPORT
nux_paint_t*
nux_paint_build_solid_color (
    nux_gvector4d_t* color,
    float global_opacity
);

NUXC_CONDITIONAL_EXPORT
nux_paint_t*
nux_paint_build_linear_gradient (
    nux_gvector2d_t* start,
    nux_gvector2d_t* end,
    nux_gradient_stop_t** stops,
    int stop_count,
    float global_opacity
);

NUXC_CONDITIONAL_EXPORT
nux_paint_t*
nux_paint_build_radial_gradient (
    nux_gvector2d_t* center,
    float radius,
    nux_gradient_stop_t** stops,
    int stop_count,
    float global_opacity
);

#endif
