// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUXC_GVECTOR2D_H_INCLUDED
#define NUXC_GVECTOR2D_H_INCLUDED

#include <nux/core.h>

typedef struct nux_gvector2d_t nux_gvector2d_t;

NUXC_CONDITIONAL_EXPORT
nux_gvector2d_t*
nux_gvector2d_create (
    float x,
    float y
);

NUXC_CONDITIONAL_EXPORT
void
nux_gvector2d_destroy (
    nux_gvector2d_t* gvector2d
);

NUXC_CONDITIONAL_EXPORT
float
nux_gvector2d_get_x (
    nux_gvector2d_t* gvector2d
);

NUXC_CONDITIONAL_EXPORT
void
nux_gvector2d_set_x (
    nux_gvector2d_t* gvector2d,
    float new_x
);

NUXC_CONDITIONAL_EXPORT
float
nux_gvector2d_get_y (
    nux_gvector2d_t* gvector2d
);

NUXC_CONDITIONAL_EXPORT
void
nux_gvector2d_set_y (
    nux_gvector2d_t* gvector2d,
    float new_y
);

#endif
