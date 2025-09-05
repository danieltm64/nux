// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/widget.h>
#include "handles.hpp"

NUXC_EXTERNC
nux_window_element_t*
nux_widget_upcast (
    nux_widget_t* widget
) {
    return nux_impl_map(
        static_cast<nux::window_element*>(nux_impl_map(widget))
    );
}

NUXC_EXTERNC
void*
nux_widget_grab_native_handle (
    nux_widget_t* widget
) {
    return &nux_impl_map(widget)->grab_native_handle();
}

NUXC_EXTERNC
bool
nux_widget_is_enabled (
    nux_widget_t* widget
) {
    auto handle{nux_impl_map(widget)};
    return handle->is_enabled();
}

NUXC_EXTERNC
void
nux_widget_set_enabled (
    nux_widget_t* widget,
    bool new_enabled
) {
    auto handle{nux_impl_map(widget)};
    handle->set_enabled(new_enabled);
}

NUXC_EXTERNC
void
nux_widget_show (
    nux_widget_t *widget
) {
    auto handle{nux_impl_map(widget)};
    handle->show();
}

NUXC_EXTERNC
void
nux_widget_hide (
    nux_widget_t *widget
) {
    auto handle{nux_impl_map(widget)};
    handle->hide();
}
