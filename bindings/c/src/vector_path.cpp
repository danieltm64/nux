// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/vector_path.h>
#include "handles.hpp"

NUXC_EXTERNC
nux_vector_path_t*
nux_vector_path_create ()
{
    return new nux_vector_path_t{nux::vector_path{}};
}

NUXC_EXTERNC
void
nux_vector_path_destroy (
    nux_vector_path_t* vector_path
) {
    delete vector_path;
}

NUXC_EXTERNC
void
nux_vector_path_begin_path (
    nux_vector_path_t* vector_path,
    float x,
    float y
) {
    vector_path->handle.begin_path(x, y);
}

NUXC_EXTERNC
void
nux_vector_path_line_to (
    nux_vector_path_t* vector_path,
    float x,
    float y
) {
    vector_path->handle.line_to(x, y);
}

NUXC_EXTERNC
void
nux_vector_path_quad_to (
    nux_vector_path_t* vector_path,
    float cx,
    float cy,
    float x,
    float y
) {
    vector_path->handle.quad_to(cx, cy, x, y);
}

NUXC_EXTERNC
void
nux_vector_path_cubic_to (
    nux_vector_path_t* vector_path,
    float cx1,
    float cy1,
    float cx2,
    float cy2,
    float x,
    float y
) {
    vector_path->handle.cubic_to(cx1, cy1, cx2, cy2, x, y);
}

NUXC_EXTERNC
void
nux_vector_path_close (
    nux_vector_path_t* vector_path
) {
    vector_path->handle.close();
}

NUXC_EXTERNC
void
nux_vector_path_end_path (
    nux_vector_path_t* vector_path
) {
    vector_path->handle.end_path();
}

NUXC_EXTERNC
nux_vector_path_t*
nux_vector_path_build_rectangle (
    float x,
    float y,
    float width,
    float height,
    float radius
) {
    return new nux_vector_path_t{
        nux::vector_path::build_rectangle(x, y, width, height, radius)
    };
}

NUXC_EXTERNC
nux_vector_path_t*
nux_vector_path_build_circle (
    float center_x,
    float center_y,
    float radius
) {
    return new nux_vector_path_t{
        nux::vector_path::build_circle(center_x, center_y, radius)
    };
}
