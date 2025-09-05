// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUXC_GVECTOR4D_H_INCLUDED
#define NUXC_GVECTOR4D_H_INCLUDED

#include <nux/core.h>

typedef struct nux_gvector4d_t nux_gvector4d_t;

NUXC_CONDITIONAL_EXPORT
nux_gvector4d_t*
nux_gvector4d_create (
    float x,
    float y,
    float z,
    float w
);

NUXC_CONDITIONAL_EXPORT
void
nux_gvector4d_destroy (
    nux_gvector4d_t* gvector4d
);

NUXC_CONDITIONAL_EXPORT
float
nux_gvector4d_get_x (
    nux_gvector4d_t* gvector4d
);

NUXC_CONDITIONAL_EXPORT
void
nux_gvector4d_set_x (
    nux_gvector4d_t* gvector4d,
    float new_x
);

NUXC_CONDITIONAL_EXPORT
float
nux_gvector4d_get_y (
    nux_gvector4d_t* gvector4d
);

NUXC_CONDITIONAL_EXPORT
void
nux_gvector4d_set_y (
    nux_gvector4d_t* gvector4d,
    float new_y
);

NUXC_CONDITIONAL_EXPORT
float
nux_gvector4d_get_z (
    nux_gvector4d_t* gvector4d
);

NUXC_CONDITIONAL_EXPORT
void
nux_gvector4d_set_z (
    nux_gvector4d_t* gvector4d,
    float new_z
);

NUXC_CONDITIONAL_EXPORT
float
nux_gvector4d_get_w (
    nux_gvector4d_t* gvector4d
);

NUXC_CONDITIONAL_EXPORT
void
nux_gvector4d_set_w (
    nux_gvector4d_t* gvector4d,
    float new_w
);

#endif
