// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUXC_GROUP_BOX_H_INCLUDED
#define NUXC_GROUP_BOX_H_INCLUDED

#include <nux/layout.h>

typedef struct nux_group_box_t nux_group_box_t;

NUXC_CONDITIONAL_EXPORT
nux_group_box_t*
nux_group_box_create (
    nux_window_element_t* parent
);

NUXC_CONDITIONAL_EXPORT
void
nux_group_box_destroy (
    nux_group_box_t* group_box
);

NUXC_CONDITIONAL_EXPORT
nux_widget_t*
nux_group_box_upcast (
    nux_group_box_t* group_box
);

NUXC_CONDITIONAL_EXPORT
nux_layout_t*
nux_group_box_grab_content_layout (
    nux_group_box_t* group_box
);

NUXC_CONDITIONAL_EXPORT
const nuxchar_t*
nux_group_box_get_title (
    nux_group_box_t* group_box,
    int* size
);

NUXC_CONDITIONAL_EXPORT
void
nux_group_box_set_title (
    nux_group_box_t* group_box,
    const nuxchar_t* new_title
);

NUXC_CONDITIONAL_EXPORT
void
nux_group_box_add_widget (
    nux_group_box_t* group_box,
    nux_widget_t* child
);

#endif
