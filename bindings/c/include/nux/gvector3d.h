// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUXC_GVECTOR3D_H_INCLUDED
#define NUXC_GVECTOR3D_H_INCLUDED

#include <nux/core.h>

typedef struct nux_gvector3d_t nux_gvector3d_t;

NUXC_CONDITIONAL_EXPORT
nux_gvector3d_t*
nux_gvector3d_create (
    float x,
    float y,
    float z
);

NUXC_CONDITIONAL_EXPORT
void
nux_gvector3d_destroy (
    nux_gvector3d_t* gvector3d
);

NUXC_CONDITIONAL_EXPORT
float
nux_gvector3d_get_x (
    nux_gvector3d_t* gvector3d
);

NUXC_CONDITIONAL_EXPORT
void
nux_gvector3d_set_x (
    nux_gvector3d_t* gvector3d,
    float new_x
);

NUXC_CONDITIONAL_EXPORT
float
nux_gvector3d_get_y (
    nux_gvector3d_t* gvector3d
);

NUXC_CONDITIONAL_EXPORT
void
nux_gvector3d_set_y (
    nux_gvector3d_t* gvector3d,
    float new_y
);

NUXC_CONDITIONAL_EXPORT
float
nux_gvector3d_get_z (
    nux_gvector3d_t* gvector3d
);

NUXC_CONDITIONAL_EXPORT
void
nux_gvector3d_set_z (
    nux_gvector3d_t* gvector3d,
    float new_z
);

#endif
