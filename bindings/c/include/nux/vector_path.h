// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUXC_VECTOR_PATH_H_INCLUDED
#define NUXC_VECTOR_PATH_H_INCLUDED

#include <nux/core.h>

typedef struct nux_vector_path_t nux_vector_path_t;

NUXC_CONDITIONAL_EXPORT
nux_vector_path_t*
nux_vector_path_create ();

NUXC_CONDITIONAL_EXPORT
void
nux_vector_path_destroy (
    nux_vector_path_t* vector_path
);

NUXC_CONDITIONAL_EXPORT
void
nux_vector_path_begin_path (
    nux_vector_path_t* vector_path,
    float x,
    float y
);

NUXC_CONDITIONAL_EXPORT
void
nux_vector_path_line_to (
    nux_vector_path_t* vector_path,
    float x,
    float y
);

NUXC_CONDITIONAL_EXPORT
void
nux_vector_path_quad_to (
    nux_vector_path_t* vector_path,
    float cx,
    float cy,
    float x,
    float y
);

NUXC_CONDITIONAL_EXPORT
void
nux_vector_path_cubic_to (
    nux_vector_path_t* vector_path,
    float cx1,
    float cy1,
    float cx2,
    float cy2,
    float x,
    float y
);

NUXC_CONDITIONAL_EXPORT
void
nux_vector_path_close (
    nux_vector_path_t* vector_path
);

NUXC_CONDITIONAL_EXPORT
void
nux_vector_path_end_path (
    nux_vector_path_t* vector_path
);

NUXC_CONDITIONAL_EXPORT
nux_vector_path_t*
nux_vector_path_build_rectangle (
    float x,
    float y,
    float width,
    float height,
    float radius
);

NUXC_CONDITIONAL_EXPORT
nux_vector_path_t*
nux_vector_path_build_circle (
    float center_x,
    float center_y,
    float radius
);

#endif
