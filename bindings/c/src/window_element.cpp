// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/window_element.h>
#include "handles.hpp"

NUXC_EXTERNC
int
nux_window_element_get_x (
    nux_window_element_t* window_element
) {
    auto handle{nux_impl_map(window_element)};
    return handle->get_x();
}

NUXC_EXTERNC
void
nux_window_element_set_x (
    nux_window_element_t* window_element,
    int new_x
) {
    auto handle{nux_impl_map(window_element)};
    handle->set_x(new_x);
}

NUXC_EXTERNC
int
nux_window_element_get_y (
    nux_window_element_t* window_element
) {
    auto handle{nux_impl_map(window_element)};
    return handle->get_y();
}

NUXC_EXTERNC
void
nux_window_element_set_y (
    nux_window_element_t* window_element,
    int new_y
) {
    auto handle{nux_impl_map(window_element)};
    handle->set_y(new_y);
}

NUXC_EXTERNC
void
nux_window_element_get_position (
    nux_window_element_t* window_element,
    int* x,
    int* y
) {
    auto handle{nux_impl_map(window_element)};
    int current_x;
    int current_y;
    handle->get_position(current_x, current_y);
    if (x) {
        *x = current_x;
    }
    if (y) {
        *y = current_y;
    }
}

NUXC_EXTERNC
void
nux_window_element_set_position (
    nux_window_element_t* window_element,
    int new_x,
    int new_y
) {
    auto handle{nux_impl_map(window_element)};
    handle->set_position(new_x, new_y);
}

NUXC_EXTERNC
int
nux_window_element_get_width (
    nux_window_element_t* window_element
) {
    auto handle{nux_impl_map(window_element)};
    return handle->get_width();
}

NUXC_EXTERNC
void
nux_window_element_set_width (
    nux_window_element_t* window_element,
    int new_width
) {
    auto handle{nux_impl_map(window_element)};
    handle->set_width(new_width);
}

NUXC_EXTERNC
int
nux_window_element_get_height (
    nux_window_element_t* window_element
) {
    auto handle{nux_impl_map(window_element)};
    return handle->get_height();
}

NUXC_EXTERNC
void
nux_window_element_set_height (
    nux_window_element_t* window_element,
    int new_height
) {
    auto handle{nux_impl_map(window_element)};
    handle->set_height(new_height);
}

NUXC_EXTERNC
void
nux_window_element_get_size (
    nux_window_element_t* window_element,
    int* width,
    int* height
) {
    auto handle{nux_impl_map(window_element)};
    int current_width;
    int current_height;
    handle->get_size(current_width, current_height);
    if (width) {
        *width = current_width;
    }
    if (height) {
        *height = current_height;
    }
}

NUXC_EXTERNC
void
nux_window_element_set_size (
    nux_window_element_t* window_element,
    int new_width,
    int new_height
) {
    auto handle{nux_impl_map(window_element)};
    handle->set_size(new_width, new_height);
}

NUXC_EXTERNC
int
nux_window_element_get_horizontal_overhead (
    nux_window_element_t* window_element
) {
    auto handle{nux_impl_map(window_element)};
    return handle->get_horizontal_overhead();
}

NUXC_EXTERNC
int
nux_window_element_get_vertical_overhead (
    nux_window_element_t* window_element
) {
    auto handle{nux_impl_map(window_element)};
    return handle->get_vertical_overhead();
}

NUXC_EXTERNC
bool
nux_window_element_is_dynamically_sized (
    nux_window_element_t* window_element
) {
    auto handle{nux_impl_map(window_element)};
    return handle->is_dynamically_sized();
}

NUXC_EXTERNC
void
nux_window_element_set_dynamically_sized (
    nux_window_element_t* window_element,
    bool new_value
) {
    auto handle{nux_impl_map(window_element)};
    handle->set_dynamically_sized(new_value);
}