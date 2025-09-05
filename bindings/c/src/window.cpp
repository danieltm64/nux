// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/window.h>
#include "handles.hpp"

NUXC_EXTERNC
nux_window_t*
nux_window_create (
    const nuxchar_t* initial_title,
    int initial_width,
    int initial_height,
    nux_window_mode_t initial_mode
) {
    return new nux_window_t{
        nuxc_window{
            nux_impl_map(initial_title),
            initial_width,
            initial_height,
            nux_impl_map(initial_mode),
            nullptr,
            nullptr
        }
    };
}

NUXC_EXTERNC
void
nux_window_destroy (
    nux_window_t* window
) {
    delete window;
}

NUXC_EXTERNC
nux_layout_t*
nux_window_grab_root_layout (
    nux_window_t* window
) {
    return nux_impl_map(window->handle.grab_root_layout());
}

NUXC_EXTERNC
void
nux_window_get_size (
    nux_window_t* window,
    int *width,
    int *height
) {
    int w;
    int h;
    window->handle.get_size(w, h);
    if (width) {
        *width = w;
    }
    if (height) {
        *height = h;
    }
}

NUXC_EXTERNC
void
nux_window_set_size (
    nux_window_t* window,
    int new_width,
    int new_height
) {
    window->handle.set_size(new_width, new_height);
}

NUXC_EXTERNC
const nuxchar_t*
nux_window_get_title (
    nux_window_t* window,
    int* size
) {
    window->title = window->handle.get_title();
    if (size) {
        *size = window->title.size();
    }
    return reinterpret_cast<const nuxchar_t*>(window->title.data());
}

NUXC_EXTERNC
void
nux_window_set_title (
    nux_window_t* window,
    const nuxchar_t* title
) {
    window->handle.set_title(
        reinterpret_cast<nux::string_view::const_pointer>(title)
    );
}

NUXC_EXTERNC
void
nux_window_show (
    nux_window_t* window
) {
    window->handle.show();
}
NUXC_EXTERNC
void
nux_window_hide (
    nux_window_t* window
) {
    window->handle.hide();
}

NUXC_EXTERNC
void
nux_window_center (
    nux_window_t *window
) {
    window->handle.center();
}

NUXC_EXTERNC
nux_window_close_event_handler_t
nux_window_get_close_event_handler (
    nux_window_t* window
) {
    return window->handle.m_close_event_handler;
}

NUXC_EXTERNC
void
nux_window_set_close_event_handler (
    nux_window_t* window,
    nux_window_close_event_handler_t event_handler,
    void* user_data
) {
    window->handle.m_close_event_handler = event_handler;
    window->handle.m_close_event_user_data = user_data;
}
