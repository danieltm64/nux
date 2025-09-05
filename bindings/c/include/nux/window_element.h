// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUXC_WINDOW_ELEMENT_H_INCLUDED
#define NUXC_WINDOW_ELEMENT_H_INCLUDED

#include <nux/core.h>

typedef struct nux_window_element_t nux_window_element_t;

#define NUXC_WINDOW_ELEMENT(window_element) ((nux_window_element_t*)window_element)

NUXC_CONDITIONAL_EXPORT
int
nux_window_element_get_x (
    nux_window_element_t* window_element
);

NUXC_CONDITIONAL_EXPORT
void
nux_window_element_set_x (
    nux_window_element_t* window_element,
    int new_x
);

NUXC_CONDITIONAL_EXPORT
int
nux_window_element_get_y (
    nux_window_element_t* window_element
);

NUXC_CONDITIONAL_EXPORT
void
nux_window_element_set_y (
    nux_window_element_t* window_element,
    int new_y
);

NUXC_CONDITIONAL_EXPORT
void
nux_window_element_get_position (
    nux_window_element_t* window_element,
    int* x,
    int* y
    );

NUXC_CONDITIONAL_EXPORT
void
nux_window_element_set_position (
    nux_window_element_t* window_element,
    int new_x,
    int new_y
);

NUXC_CONDITIONAL_EXPORT
int
nux_window_element_get_width (
    nux_window_element_t* window_element
);

NUXC_CONDITIONAL_EXPORT
void
nux_window_element_set_width (
    nux_window_element_t* window_element,
    int new_width
);

NUXC_CONDITIONAL_EXPORT
int
nux_window_element_get_height (
    nux_window_element_t* window_element
);

NUXC_CONDITIONAL_EXPORT
void
nux_window_element_set_height (
    nux_window_element_t* window_element,
    int new_height
);

NUXC_CONDITIONAL_EXPORT
void
nux_window_element_get_size (
    nux_window_element_t* window_element,
    int* width,
    int* height
);

NUXC_CONDITIONAL_EXPORT
void
nux_window_element_set_size (
    nux_window_element_t* window_element,
    int new_width,
    int new_height
);

NUXC_CONDITIONAL_EXPORT
int
nux_window_element_get_horizontal_overhead (
    nux_window_element_t* window_element
);

NUXC_CONDITIONAL_EXPORT
int
nux_window_element_get_vertical_overhead (
    nux_window_element_t* window_element
);

NUXC_CONDITIONAL_EXPORT
bool
nux_window_element_is_dynamically_sized (
    nux_window_element_t* window_element
);

NUXC_CONDITIONAL_EXPORT
void
nux_window_element_set_dynamically_sized (
    nux_window_element_t* window_element,
    bool new_value
);

#endif
