// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/gvector3d.h>
#include "handles.hpp"

NUXC_EXTERNC
nux_gvector3d_t*
nux_gvector3d_create (
    float x,
    float y,
    float z
) {
    return new nux_gvector3d_t{nux::gvector3d<float>{x, y, z}};
}

NUXC_EXTERNC
void
nux_gvector3d_destroy (
    nux_gvector3d_t* gvector3d
) {
    delete gvector3d;
}

NUXC_EXTERNC
float
nux_gvector3d_get_x (
    nux_gvector3d_t* gvector3d
) {
    return gvector3d->handle.x;
}

NUXC_EXTERNC
void
nux_gvector3d_set_x (
    nux_gvector3d_t* gvector3d,
    float new_x
) {
    gvector3d->handle.x = new_x;
}

NUXC_EXTERNC
float
nux_gvector3d_get_y (
    nux_gvector3d_t* gvector3d
) {
    return gvector3d->handle.y;
}

NUXC_EXTERNC
void
nux_gvector3d_set_y (
    nux_gvector3d_t* gvector3d,
    float new_y
) {
    gvector3d->handle.y = new_y;
}

NUXC_EXTERNC
float
nux_gvector3d_get_z (
    nux_gvector3d_t* gvector3d
) {
    return gvector3d->handle.z;
}

NUXC_EXTERNC
void
nux_gvector3d_set_z (
    nux_gvector3d_t* gvector3d,
    float new_z
) {
    gvector3d->handle.z = new_z;
}
