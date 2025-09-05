// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUXC_WINDOW_H_INCLUDED
#define NUXC_WINDOW_H_INCLUDED

#include <nux/close_event.h>
#include <nux/layout.h>

typedef struct nux_window_t nux_window_t;

typedef NUXC_ENUM(int32_t, nux_window_mode_t) {
    NUXC_WINDOW_MODE_STANDARD,
    NUXC_WINDOW_MODE_MAXIMIZED,
    NUXC_WINDOW_MODE_MINIMIZED
} nux_window_mode_t;

typedef void (*nux_window_close_event_handler_t)(nux_window_t* window, nux_close_event_t* ev, void* user_data);

NUXC_CONDITIONAL_EXPORT
nux_window_t*
nux_window_create (
    const nuxchar_t* initial_title,
    int initial_width,
    int initial_height,
    nux_window_mode_t initial_mode
);

NUXC_CONDITIONAL_EXPORT
void
nux_window_destroy (
    nux_window_t* window
);

NUXC_CONDITIONAL_EXPORT
nux_layout_t*
nux_window_grab_root_layout (
    nux_window_t* window
);

NUXC_CONDITIONAL_EXPORT
void
nux_window_get_size (
    nux_window_t* window,
    int* width,
    int* height
);

NUXC_CONDITIONAL_EXPORT
void
nux_window_set_size (
    nux_window_t* window,
    int new_width,
    int new_height
);

NUXC_CONDITIONAL_EXPORT
const nuxchar_t*
nux_window_get_title (
    nux_window_t* window,
    int* size
);

NUXC_CONDITIONAL_EXPORT
void
nux_window_set_title (
    nux_window_t* window,
    const nuxchar_t* title
);

NUXC_CONDITIONAL_EXPORT
void
nux_window_show (
    nux_window_t* window
);

NUXC_CONDITIONAL_EXPORT
void
nux_window_hide (
    nux_window_t* window
);

NUXC_CONDITIONAL_EXPORT
void
nux_window_center (
    nux_window_t* window
);

NUXC_CONDITIONAL_EXPORT
nux_window_close_event_handler_t
nux_window_get_close_event_handler (
    nux_window_t* window
);

NUXC_CONDITIONAL_EXPORT
void
nux_window_set_close_event_handler (
    nux_window_t* window,
    nux_window_close_event_handler_t event_handler,
    void* user_data
);

#endif
