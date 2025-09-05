// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/gvector4d.h>
#include "handles.hpp"

NUXC_EXTERNC
nux_gvector4d_t*
nux_gvector4d_create (
    float x,
    float y,
    float z,
    float w
) {
    return new nux_gvector4d_t{nux::gvector4d<float>{x, y, z, w}};
}

NUXC_EXTERNC
void
nux_gvector4d_destroy (
    nux_gvector4d_t* gvector4d
) {
    delete gvector4d;
}

NUXC_EXTERNC
float
nux_gvector4d_get_x (
    nux_gvector4d_t* gvector4d
) {
    return gvector4d->handle.x;
}

NUXC_EXTERNC
void
nux_gvector4d_set_x (
    nux_gvector4d_t* gvector4d,
    float new_x
) {
    gvector4d->handle.x = new_x;
}

NUXC_EXTERNC
float
nux_gvector4d_get_y (
    nux_gvector4d_t* gvector4d
) {
    return gvector4d->handle.y;
}

NUXC_EXTERNC
void
nux_gvector4d_set_y (
    nux_gvector4d_t* gvector4d,
    float new_y
) {
    gvector4d->handle.y = new_y;
}

NUXC_EXTERNC
float
nux_gvector4d_get_z (
    nux_gvector4d_t* gvector4d
) {
    return gvector4d->handle.z;
}

NUXC_EXTERNC
void
nux_gvector4d_set_z (
    nux_gvector4d_t* gvector4d,
    float new_z
) {
    gvector4d->handle.z = new_z;
}

NUXC_EXTERNC
float
nux_gvector4d_get_w (
    nux_gvector4d_t* gvector4d
) {
    return gvector4d->handle.w;
}

NUXC_EXTERNC
void
nux_gvector4d_set_w (
    nux_gvector4d_t* gvector4d,
    float new_w
) {
    gvector4d->handle.w = new_w;
}
