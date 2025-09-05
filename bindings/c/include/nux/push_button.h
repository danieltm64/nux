// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUXC_PUSH_BUTTON_H_INCLUDED
#define NUXC_PUSH_BUTTON_H_INCLUDED

#include <nux/group_box.h>

typedef struct nux_push_button_t nux_push_button_t;

typedef void (*nux_push_button_trigger_event_handler_t)(nux_push_button_t* push_button, void* user_data);

NUXC_CONDITIONAL_EXPORT
nux_push_button_t*
nux_push_button_create (
    nux_window_element_t* parent
);

NUXC_CONDITIONAL_EXPORT
void
nux_push_button_destroy (
    nux_push_button_t* push_button
);

NUXC_CONDITIONAL_EXPORT
nux_widget_t*
nux_push_button_upcast (
    nux_push_button_t* push_button
);

NUXC_CONDITIONAL_EXPORT
const nuxchar_t*
nux_push_button_get_text (
    nux_push_button_t* push_button,
    int* size
);

NUXC_CONDITIONAL_EXPORT
void
nux_push_button_set_text (
    nux_push_button_t* push_button,
    const nuxchar_t* new_text
);

NUXC_CONDITIONAL_EXPORT
nux_push_button_trigger_event_handler_t
nux_push_button_get_trigger_event_handler (
    nux_push_button_t* push_button
);

NUXC_CONDITIONAL_EXPORT
void
nux_push_button_set_trigger_event_handler (
    nux_push_button_t* push_button,
    nux_push_button_trigger_event_handler_t event_handler,
    void* user_data
);

#endif
