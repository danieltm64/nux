// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUXC_RADIO_BUTTON_H_INCLUDED
#define NUXC_RADIO_BUTTON_H_INCLUDED

#include <nux/group_box.h>
#include <nux/check_group.h>

typedef struct nux_radio_button_t nux_radio_button_t;

typedef void (*nux_radio_button_toggle_event_handler_t)(nux_radio_button_t* radio_button, void* user_data);

NUXC_CONDITIONAL_EXPORT
nux_radio_button_t*
nux_radio_button_create (
    nux_window_element_t* parent,
    nux_check_group_t* group
);

NUXC_CONDITIONAL_EXPORT
void
nux_radio_button_destroy (
    nux_radio_button_t* radio_button
);

NUXC_CONDITIONAL_EXPORT
nux_widget_t*
nux_radio_button_upcast (
    nux_radio_button_t* radio_button
);

NUXC_CONDITIONAL_EXPORT
const nuxchar_t*
nux_radio_button_get_text (
    nux_radio_button_t* radio_button,
    int* size
);

NUXC_CONDITIONAL_EXPORT
void
nux_radio_button_set_text (
    nux_radio_button_t* radio_button,
    const nuxchar_t* new_text
);

NUXC_CONDITIONAL_EXPORT
bool
nux_radio_button_is_checked (
    nux_radio_button_t* radio_button
);

NUXC_CONDITIONAL_EXPORT
void
nux_radio_button_set_checked (
    nux_radio_button_t* radio_button,
    bool checked
);

NUXC_CONDITIONAL_EXPORT
nux_radio_button_toggle_event_handler_t
nux_radio_button_get_toggle_event_handler (
    nux_radio_button_t* radio_button
);

NUXC_CONDITIONAL_EXPORT
void
nux_radio_button_set_toggle_event_handler (
    nux_radio_button_t* radio_button,
    nux_radio_button_toggle_event_handler_t event_handler,
    void* user_data
);

#endif
