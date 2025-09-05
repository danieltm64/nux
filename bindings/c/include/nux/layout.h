// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUXC_LAYOUT_H_INCLUDED
#define NUXC_LAYOUT_H_INCLUDED

#include <nux/window_element.h>
#include <nux/widget.h>

typedef struct nux_layout_t nux_layout_t;

typedef NUXC_ENUM(int32_t, nux_layout_kind_t) {
    NUXC_LAYOUT_KIND_FIXED,
    NUXC_LAYOUT_KIND_FLOW,
} nux_layout_kind_t;

typedef NUXC_ENUM(int32_t, nux_layout_axis_t) {
    NUXC_LAYOUT_AXIS_HORIZONTAL,
    NUXC_LAYOUT_AXIS_VERTICAL
} nux_layout_axis_t;

typedef NUXC_ENUM(int32_t, nux_layout_direction_t) {
    NUXC_LAYOUT_DIRECTION_FORWARD,
    NUXC_LAYOUT_DIRECTION_REVERSE
} nux_layout_direction_t;

NUXC_CONDITIONAL_EXPORT
nux_layout_t*
nux_layout_create (
    nux_layout_t* parent,
    nux_layout_kind_t initial_kind,
    nux_layout_axis_t initial_axis,
    nux_layout_direction_t initial_direction
);

NUXC_CONDITIONAL_EXPORT
void
nux_layout_destroy (
    nux_layout_t* layout
);

NUXC_CONDITIONAL_EXPORT
nux_window_element_t*
nux_layout_upcast (
    nux_layout_t* layout
);

NUXC_CONDITIONAL_EXPORT
nux_layout_t*
nux_layout_grab_parent (
    nux_layout_t* layout
);

NUXC_CONDITIONAL_EXPORT
nux_layout_kind_t
nux_layout_get_kind (
    nux_layout_t* layout
);

NUXC_CONDITIONAL_EXPORT
void
nux_layout_set_kind (
    nux_layout_t* layout,
    nux_layout_kind_t new_kind
);

NUXC_CONDITIONAL_EXPORT
nux_layout_axis_t
nux_layout_get_axis (
    nux_layout_t* layout
);

NUXC_CONDITIONAL_EXPORT
void
nux_layout_set_axis (
    nux_layout_t* layout,
    nux_layout_axis_t new_axis
);

NUXC_CONDITIONAL_EXPORT
nux_layout_direction_t
nux_layout_get_direction (
    nux_layout_t* layout
);

NUXC_CONDITIONAL_EXPORT
void
nux_layout_set_direction (
    nux_layout_t* layout,
    nux_layout_direction_t new_direction
);

NUXC_CONDITIONAL_EXPORT
void
nux_layout_show (
    nux_layout_t* layout
);

NUXC_CONDITIONAL_EXPORT
void
nux_layout_hide (
    nux_layout_t* layout
);

NUXC_CONDITIONAL_EXPORT
void
nux_layout_add_widget (
    nux_layout_t* layout,
    nux_widget_t* child
);

NUXC_CONDITIONAL_EXPORT
void
nux_layout_add_layout (
    nux_layout_t *layout,
    nux_layout_t* child
);

#endif
