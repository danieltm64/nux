// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUXC_GRAPHICS_BOX_H_INCLUDED
#define NUXC_GRAPHICS_BOX_H_INCLUDED

#include <nux/group_box.h>
#include <nux/vector_path.h>
#include <nux/paint.h>

typedef struct nux_graphics_box_t nux_graphics_box_t;

typedef void (*nux_graphics_box_render_event_handler_t)(nux_graphics_box_t* graphics_box, void* user_data);

NUXC_CONDITIONAL_EXPORT
nux_graphics_box_t*
nux_graphics_box_create (
    nux_window_element_t* parent
);

NUXC_CONDITIONAL_EXPORT
void
nux_graphics_box_destroy (
    nux_graphics_box_t* graphics_box
);

NUXC_CONDITIONAL_EXPORT
nux_widget_t*
nux_graphics_box_upcast (
    nux_graphics_box_t* graphics_box
);

NUXC_CONDITIONAL_EXPORT
void
nux_graphics_box_clear (
    nux_graphics_box_t* graphics_box,
    float red,
    float green,
    float blue,
    float alpha
);

NUXC_CONDITIONAL_EXPORT
void
nux_graphics_box_fill_path (
    nux_graphics_box_t* graphics_box,
    nux_vector_path_t* path,
    nux_paint_t* fill_paint
);

NUXC_CONDITIONAL_EXPORT
void
nux_graphics_box_stroke_path (
    nux_graphics_box_t* graphics_box,
    nux_vector_path_t* path,
    nux_paint_t* stroke_paint
);

NUXC_CONDITIONAL_EXPORT
void
nux_graphics_box_present (
    nux_graphics_box_t* graphics_box
);

NUXC_CONDITIONAL_EXPORT
void
nux_graphics_box_render (
    nux_graphics_box_t* graphics_box
);

NUXC_CONDITIONAL_EXPORT
nux_graphics_box_render_event_handler_t
nux_graphics_box_get_render_event_handler (
    nux_graphics_box_t* graphics_box
);

NUXC_CONDITIONAL_EXPORT
void
nux_graphics_box_set_render_event_handler (
    nux_graphics_box_t* graphics_box,
    nux_graphics_box_render_event_handler_t event_handler,
    void* user_data
);

#endif
