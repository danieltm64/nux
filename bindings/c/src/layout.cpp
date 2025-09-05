// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/layout.h>
#include "handles.hpp"

NUXC_EXTERNC
nux_layout_t*
nux_layout_create (
    nux_layout_t* parent,
    nux_layout_kind_t initial_kind,
    nux_layout_axis_t initial_axis,
    nux_layout_direction_t initial_direction
) {
    return new nux_layout_t{
        nux::layout{
            parent->handle,
            nux_impl_map(initial_kind),
            nux_impl_map(initial_axis),
            nux_impl_map(initial_direction)
        }
    };
}

NUXC_EXTERNC
void
nux_layout_destroy (
    nux_layout_t* layout
) {
    delete layout;
}

NUXC_EXTERNC
nux_window_element_t*
nux_layout_upcast (
    nux_layout_t* layout
) {
    return nux_impl_map(
        static_cast<nux::window_element*>(nux_impl_map(layout))
    );
}

NUXC_EXTERNC
nux_layout_kind_t
nux_layout_get_kind (
    nux_layout_t* layout
) {
    return nux_impl_map(layout->handle.get_kind());
}

NUXC_EXTERNC
nux_layout_t*
nux_layout_grab_parent (
    nux_layout_t* layout
) {
    return nux_impl_map(layout->handle.grab_parent());
}

NUXC_EXTERNC
void
nux_layout_set_kind (
    nux_layout_t* layout,
    nux_layout_kind_t new_kind
) {
    layout->handle.set_kind(nux_impl_map(new_kind));
}

NUXC_EXTERNC
nux_layout_axis_t
nux_layout_get_axis (
    nux_layout_t* layout
) {
    return nux_impl_map(layout->handle.get_axis());
}

NUXC_EXTERNC
void
nux_layout_set_axis (
    nux_layout_t* layout,
    nux_layout_axis_t new_axis
) {
    layout->handle.set_axis(nux_impl_map(new_axis));
}

NUXC_EXTERNC
nux_layout_direction_t
nux_layout_get_direction (
    nux_layout_t* layout
) {
    return nux_impl_map(layout->handle.get_direction());
}

NUXC_EXTERNC
void
nux_layout_set_direction (
    nux_layout_t* layout,
    nux_layout_direction_t new_direction
) {
    layout->handle.set_direction(nux_impl_map(new_direction));
}

NUXC_EXTERNC
void
nux_layout_show (
    nux_layout_t* layout
) {
    auto handle{nux_impl_map(layout)};
    handle->show();
}

NUXC_EXTERNC
void
nux_layout_hide (
    nux_layout_t* layout
) {
    auto handle{nux_impl_map(layout)};
    handle->hide();
}

NUXC_EXTERNC
void
nux_layout_add_widget (
    nux_layout_t* layout,
    nux_widget_t* child
) {
    auto layout_handle{nux_impl_map(layout)};
    auto child_handle{nux_impl_map(child)};
    layout_handle->grab_children().push_back(
        std::unique_ptr<nux::widget>{child_handle}
    );
    layout_handle->update();
}

NUXC_EXTERNC
void
nux_layout_add_layout (
    nux_layout_t *layout,
    nux_layout_t* child
) {
    auto layout_handle{nux_impl_map(layout)};
    auto child_handle{nux_impl_map(child)};
    layout_handle->grab_children().push_back(
        std::unique_ptr<nux::layout>{child_handle}
    );
    layout_handle->update();
}
