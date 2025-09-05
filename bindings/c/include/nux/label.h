// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUXC_LABEL_H_INCLUDED
#define NUXC_LABEL_H_INCLUDED

#include <nux/group_box.h>

typedef struct nux_label_t nux_label_t;

NUXC_CONDITIONAL_EXPORT
nux_label_t*
nux_label_create (
    nux_window_element_t* parent
);

NUXC_CONDITIONAL_EXPORT
void
nux_label_destroy (
    nux_label_t* label
);

NUXC_CONDITIONAL_EXPORT
nux_widget_t*
nux_label_upcast (
    nux_label_t* label
);

NUXC_CONDITIONAL_EXPORT
const nuxchar_t*
nux_label_get_text (
    nux_label_t* label,
    int* size
);

NUXC_CONDITIONAL_EXPORT
void
nux_label_set_text (
    nux_label_t* label,
    const nuxchar_t* new_text
);

#endif
