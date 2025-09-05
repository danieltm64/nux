// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUXC_WIDGET_H_INCLUDED
#define NUXC_WIDGET_H_INCLUDED

#include <nux/core.h>

typedef struct nux_widget_t nux_widget_t;

#define NUXC_WIDGET(widget) ((nux_widget_t*)widget)

NUXC_CONDITIONAL_EXPORT
nux_window_element_t*
nux_widget_upcast (
    nux_widget_t* widget
);

NUXC_CONDITIONAL_EXPORT
void*
nux_widget_grab_native_handle (
    nux_widget_t* widget
);

NUXC_CONDITIONAL_EXPORT
bool
nux_widget_is_enabled (
    nux_widget_t* widget
);

NUXC_CONDITIONAL_EXPORT
void
nux_widget_set_enabled (
    nux_widget_t* widget,
    bool new_enabled
);

NUXC_CONDITIONAL_EXPORT
void
nux_widget_show (
    nux_widget_t* widget
);

NUXC_CONDITIONAL_EXPORT
void
nux_widget_hide (
    nux_widget_t* widget
);

#endif
