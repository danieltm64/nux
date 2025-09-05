// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUXC_CHECK_BOX_H_INCLUDED
#define NUXC_CHECK_BOX_H_INCLUDED

#include <nux/group_box.h>

typedef struct nux_check_box_t nux_check_box_t;

typedef void (*nux_check_box_toggle_event_handler_t)(nux_check_box_t* check_box, void* user_data);

NUXC_CONDITIONAL_EXPORT
nux_check_box_t*
nux_check_box_create (
    nux_window_element_t* parent
);

NUXC_CONDITIONAL_EXPORT
void
nux_check_box_destroy (
    nux_check_box_t* check_box
);

NUXC_CONDITIONAL_EXPORT
nux_widget_t*
nux_check_box_upcast (
    nux_check_box_t* check_box
);

NUXC_CONDITIONAL_EXPORT
const nuxchar_t*
nux_check_box_get_text (
    nux_check_box_t* check_box,
    int* size
);

NUXC_CONDITIONAL_EXPORT
void
nux_check_box_set_text (
    nux_check_box_t* check_box,
    const nuxchar_t* new_text
);

NUXC_CONDITIONAL_EXPORT
bool
nux_check_box_is_checked (
    nux_check_box_t* check_box
);

NUXC_CONDITIONAL_EXPORT
void
nux_check_box_set_checked (
    nux_check_box_t* check_box,
    bool checked
);

NUXC_CONDITIONAL_EXPORT
nux_check_box_toggle_event_handler_t
nux_check_box_get_toggle_event_handler (
    nux_check_box_t* check_box
);

NUXC_CONDITIONAL_EXPORT
void
nux_check_box_set_toggle_event_handler (
    nux_check_box_t* check_box,
    nux_check_box_toggle_event_handler_t event_handler,
    void* user_data
);

#endif
