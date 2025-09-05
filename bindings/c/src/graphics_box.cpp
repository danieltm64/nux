// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/graphics_box.h>
#include "handles.hpp"

NUXC_EXTERNC
nux_graphics_box_t*
nux_graphics_box_create (
    nux_window_element_t* parent
) {
    auto element{nux_impl_map(parent)};

    if (
        auto enclosing_layout{dynamic_cast<nux::layout*>(element)};
        enclosing_layout
    ) {
        auto result{
            new nux_graphics_box_t{
                nux::graphics_box{*enclosing_layout},
                nullptr,
                nullptr
            }
        };
        result->handle.set_render_event_handler(
            [result] () {
                if (result->render_event_handler) {
                    result->render_event_handler(
                        result,
                        result->render_event_user_data
                    );
                }
            }
        );
        return result;
    }

    if (
        auto enclosing_group_box{dynamic_cast<nux::group_box*>(element)};
        enclosing_group_box
    ) {
        auto result{
            new nux_graphics_box_t{
                nux::graphics_box{
                    enclosing_group_box->grab_native_handle(),
                    enclosing_group_box->grab_content_layout()
                },
                nullptr,
                nullptr
            }
        };
        result->handle.set_render_event_handler(
            [result] () {
                if (result->render_event_handler) {
                    result->render_event_handler(
                        result,
                        result->render_event_user_data
                    );
                }
            }
        );
        return result;
    }

    return nullptr;
}

NUXC_EXTERNC
void
nux_graphics_box_destroy (
    nux_graphics_box_t* graphics_box
) {
    delete graphics_box;
}

NUXC_EXTERNC
nux_widget_t*
nux_graphics_box_upcast (
    nux_graphics_box_t* graphics_box
) {
    return nux_impl_map(static_cast<nux::widget*>(nux_impl_map(graphics_box)));
}

NUXC_EXTERNC
void
nux_graphics_box_clear (
    nux_graphics_box_t* graphics_box,
    float red,
    float green,
    float blue,
    float alpha
) {
    nux_impl_map(graphics_box)->clear(red, green, blue, alpha);
}

NUXC_EXTERNC
void
nux_graphics_box_fill_path (
    nux_graphics_box_t* graphics_box,
    nux_vector_path_t* path,
    nux_paint_t* fill_paint
) {
    nux_impl_map(graphics_box)->fill_path(
        *nux_impl_map(path),
        *nux_impl_map(fill_paint)
    );
}

NUXC_EXTERNC
void
nux_graphics_box_stroke_path (
    nux_graphics_box_t* graphics_box,
    nux_vector_path_t* path,
    nux_paint_t* stroke_paint
) {
    nux_impl_map(graphics_box)->stroke_path(
        *nux_impl_map(path),
        *nux_impl_map(stroke_paint)
    );
}

NUXC_EXTERNC
void
nux_graphics_box_present (
    nux_graphics_box_t* graphics_box
) {
    nux_impl_map(graphics_box)->present();
}

NUXC_EXTERNC
void
nux_graphics_box_render (
    nux_graphics_box_t* graphics_box
) {
    nux_impl_map(graphics_box)->render();
}

NUXC_EXTERNC
nux_graphics_box_render_event_handler_t
nux_graphics_box_get_render_event_handler (
    nux_graphics_box_t* graphics_box
) {
    return graphics_box->render_event_handler;
}

NUXC_EXTERNC
void
nux_graphics_box_set_render_event_handler (
    nux_graphics_box_t* graphics_box,
    nux_graphics_box_render_event_handler_t event_handler,
    void* user_data
) {
    graphics_box->render_event_handler = event_handler;
    graphics_box->render_event_user_data = user_data;
}
