// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/gvector2d.h>
#include "handles.hpp"

NUXC_EXTERNC
nux_gvector2d_t*
nux_gvector2d_create (
    float x,
    float y
) {
    return new nux_gvector2d_t{nux::gvector2d<float>{x, y}};
}

NUXC_EXTERNC
void
nux_gvector2d_destroy (
    nux_gvector2d_t* gvector2d
) {
    delete gvector2d;
}

NUXC_EXTERNC
float
nux_gvector2d_get_x (
    nux_gvector2d_t* gvector2d
) {
    return gvector2d->handle.x;
}

NUXC_EXTERNC
void
nux_gvector2d_set_x (
    nux_gvector2d_t* gvector2d,
    float new_x
) {
    gvector2d->handle.x = new_x;
}

NUXC_EXTERNC
float
nux_gvector2d_get_y (
    nux_gvector2d_t* gvector2d
) {
    return gvector2d->handle.y;
}

NUXC_EXTERNC
void
nux_gvector2d_set_y (
    nux_gvector2d_t* gvector2d,
    float new_y
) {
    gvector2d->handle.y = new_y;
}
