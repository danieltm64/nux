// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUXC_HANDLES_HPP_INCLUDED
#define NUXC_HANDLES_HPP_INCLUDED

#include <nux/application.h>
#include <nux/application.hpp>

#include <nux/event.h>
#include <nux/event.hpp>

#include <nux/close_event.h>
#include <nux/close_event.hpp>

#include <nux/window.h>
#include <nux/window.hpp>

#include <nux/window_element.h>
#include <nux/window_element.hpp>

#include <nux/widget.h>
#include <nux/widget.hpp>

#include <nux/label.h>
#include <nux/label.hpp>

#include <nux/check_group.h>
#include <nux/check_group.hpp>

#include <nux/push_button.h>
#include <nux/push_button.hpp>

#include <nux/check_box.h>
#include <nux/check_box.hpp>

#include <nux/radio_button.h>
#include <nux/radio_button.hpp>

#include <nux/gvector2d.h>
#include <nux/gvector2d.hpp>

#include <nux/gvector3d.h>
#include <nux/gvector3d.hpp>

#include <nux/gvector4d.h>
#include <nux/gvector4d.hpp>

#include <nux/paint.h>
#include <nux/paint.hpp>

#include <nux/vector_path.h>
#include <nux/vector_path.hpp>

#include <nux/graphics_box.h>
#include <nux/graphics_box.hpp>

#include <nux/group_box.h>
#include <nux/group_box.hpp>

typedef struct nux_application_t {
    nux::application handle;
} nux_application_t;

typedef struct nux_event_t {
    nux::event handle;
} nux_event_t;

typedef struct nux_close_event_t {
    nux::close_event handle;
} nux_close_event_t;

class nuxc_window
    : public nux::window {
public:
    nuxc_window (
        nux::string_view initial_title,
        int initial_width,
        int initial_height,
        nux::window_mode initial_mode,
        nux_window_close_event_handler_t initial_close_event_handler,
        void* initial_close_event_user_data
    )
        : nux::window{
            initial_title,
            initial_width,
            initial_height,
            initial_mode
        }
        , m_close_event_handler{initial_close_event_handler}
        , m_close_event_user_data{initial_close_event_user_data}
    {
    }

    void
    handle_close_event (
        nux::close_event &ev
    )
    override
    {
        if (m_close_event_handler) {
            auto this_v{reinterpret_cast<nux_window_t*>(this)};
            nux_close_event_t nuxc_ev{ev};

            m_close_event_handler(this_v, &nuxc_ev, m_close_event_user_data);
            ev.set_should_close(nuxc_ev.handle.should_close());
        }
    }

    nux_window_close_event_handler_t m_close_event_handler;
    void* m_close_event_user_data;
};

typedef struct nux_window_t {
    nuxc_window handle;
    nux::string title;
    nux_layout_t* root_layout;
} nux_window_t;

typedef struct nux_window_element_t {} nux_window_element_t;

typedef struct nux_widget_t {} nux_widget_t;

typedef struct nux_label_t {
    nux::label handle;
    nux::string text;
} nux_label_t;

typedef struct nux_check_group_t {
    nux::check_group<nux::widget> handle;
} nux_check_group_t;

typedef struct nux_push_button_t {
    nux::push_button handle;
    nux::string text;
    nux_push_button_trigger_event_handler_t trigger_event_handler;
    void* trigger_event_user_data;
} nux_push_button_t;

typedef struct nux_check_box_t {
    nux::check_box handle;
    nux::string text;
    nux_check_box_toggle_event_handler_t toggle_event_handler;
    void* toggle_event_user_data;
} nux_check_box_t;

typedef struct nux_radio_button_t {
    nux::radio_button handle;
    nux::string text;
    nux_radio_button_toggle_event_handler_t toggle_event_handler;
    void* toggle_event_user_data;
} nux_radio_button_t;

typedef struct nux_graphics_box_t {
    nux::graphics_box handle;
    nux_graphics_box_render_event_handler_t render_event_handler;
    void* render_event_user_data;
} nux_graphics_box_t;

typedef struct nux_group_box_t {
    nux::group_box handle;
    nux::string title;
} nux_group_box_t;

typedef struct nux_layout_t {
    nux::layout handle;
} nux_layout_t;

typedef struct nux_gvector2d_t {
    nux::gvector2d<float> handle;
} nux_gvector2d_t;

typedef struct nux_gvector3d_t {
    nux::gvector3d<float> handle;
} nux_gvector3d_t;

typedef struct nux_gvector4d_t {
    nux::gvector4d<float> handle;
} nux_gvector4d_t;

typedef struct nux_gradient_stop_t {
    nux::gradient_stop handle;
} nux_gradient_stop_t;

typedef struct nux_paint_t {
    nux::paint handle;
} nux_paint_t;

typedef struct nux_vector_path_t {
    nux::vector_path handle;
} nux_vector_path_t;

#if defined(NUXC_STRING_TYPE_STD_STRING)
using nuxc_unichar_t = char;
#elif defined(NUXC_STRING_TYPE_STD_U8STRING)
using nuxc_unichar_t = char8_t;
#elif defined(NUXC_STRING_TYPE_STD_U16STRING)
using nuxc_unichar_t = char16_t;
#endif

// String Mappers -------------------------------------------------------------

nuxc_unichar_t*
nux_impl_map (
    nuxchar_t* char_ptr
) {
    return reinterpret_cast<nuxc_unichar_t*>(char_ptr);
}

const nuxc_unichar_t*
nux_impl_map (
    const nuxchar_t* char_ptr
) {
    return reinterpret_cast<const nuxc_unichar_t*>(char_ptr);
}

// Encoding Mappers -----------------------------------------------------------

nux_encoding_t
nux_impl_map (
    nux::encoding encoding
) {
    return encoding == nux::encoding::utf8
        ? NUXC_ENCODING_UTF8
        : NUXC_ENCODING_UTF16;
}

// Event Type Mappers ---------------------------------------------------------

nux::event_type
nux_impl_map (
    nux_event_type_t event_type
) {
    switch (event_type) {
        case NUXC_EVENT_TYPE_KEY_EVENT: {
            return nux::event_type::key_event;
        }
        case NUXC_EVENT_TYPE_CLOSE_EVENT: {
            return nux::event_type::close_event;
        }
    }
}

nux_event_type_t
nux_impl_map (
    nux::event_type event_type
) {
    switch (event_type) {
        case nux::event_type::key_event: {
            return NUXC_EVENT_TYPE_KEY_EVENT;
        }
        case nux::event_type::close_event: {
            return NUXC_EVENT_TYPE_CLOSE_EVENT;
        }
    }
}

 // Layout Kind Mappers -------------------------------------------------------

nux::layout::kind
nux_impl_map (
    nux_layout_kind_t layout_kind
) {
    switch (layout_kind) {
        case NUXC_LAYOUT_KIND_FIXED: {
            return nux::layout::kind::fixed;
        }
        case NUXC_LAYOUT_KIND_FLOW: {
            return nux::layout::kind::flow;
        }
    }
}

nux_layout_kind_t
nux_impl_map (
    nux::layout::kind layout_kind
) {
    switch (layout_kind) {
        case nux::layout::kind::fixed: {
            return NUXC_LAYOUT_KIND_FIXED;
        }
        case nux::layout::kind::flow: {
            return NUXC_LAYOUT_KIND_FLOW;
        }
    }
}

 // Layout Axis Mappers -------------------------------------------------------

nux::layout::axis
nux_impl_map (
    nux_layout_axis_t layout_axis
) {
    switch (layout_axis) {
        case NUXC_LAYOUT_AXIS_HORIZONTAL: {
            return nux::layout::axis::horizontal;
        }
        case NUXC_LAYOUT_AXIS_VERTICAL: {
            return nux::layout::axis::vertical;
        }
    }
}

nux_layout_axis_t
nux_impl_map (
    nux::layout::axis layout_axis
) {
    switch (layout_axis) {
        case nux::layout::axis::horizontal: {
            return NUXC_LAYOUT_AXIS_HORIZONTAL;
        }
        case nux::layout::axis::vertical: {
            return NUXC_LAYOUT_AXIS_VERTICAL;
        }
    }
}

 // Layout Direction Mappers --------------------------------------------------

nux::layout::direction
nux_impl_map (
    nux_layout_direction_t layout_direction
) {
    switch (layout_direction) {
        case NUXC_LAYOUT_DIRECTION_FORWARD: {
            return nux::layout::direction::forward;
        }
        case NUXC_LAYOUT_DIRECTION_REVERSE: {
            return nux::layout::direction::reverse;
        }
    }
}

nux_layout_direction_t
nux_impl_map (
    nux::layout::direction layout_direction
) {
    switch (layout_direction) {
        case nux::layout::direction::forward: {
            return NUXC_LAYOUT_DIRECTION_FORWARD;
        }
        case nux::layout::direction::reverse: {
            return NUXC_LAYOUT_DIRECTION_REVERSE;
        }
    }
}

// Window Element Mappers -----------------------------------------------------

nux_window_element_t*
nux_impl_map (
    nux::window_element* window_element
) {
    return reinterpret_cast<nux_window_element_t*>(window_element);
}

nux::window_element*
nux_impl_map (
    nux_window_element_t* window_element
) {
    return reinterpret_cast<nux::window_element*>(window_element);
}

// Layout Mappers -------------------------------------------------------------

nux_layout_t*
nux_impl_map (
    nux::layout& layout
) {
    return reinterpret_cast<nux_layout_t*>(&layout);
}

nux::layout*
nux_impl_map (
    nux_layout_t* layout
) {
    return reinterpret_cast<nux::layout*>(layout);
}

// Widget Mappers -------------------------------------------------------------

nux::widget*
nux_impl_map (
    nux_widget_t* widget
) {
    return reinterpret_cast<nux::widget*>(widget);
}

nux_widget_t*
nux_impl_map (
    nux::widget* widget
) {
    return reinterpret_cast<nux_widget_t*>(widget);
}

// Check Group Mappers --------------------------------------------------------

nux::check_group<nux::widget>*
nux_impl_map (
    nux_check_group_t* check_group
) {
    return &check_group->handle;
}

nux_check_group_t*
nux_impl_map (
    nux::check_group<nux::widget>* check_group
) {
    return reinterpret_cast<nux_check_group_t*>(check_group);
}

// Label Mappers --------------------------------------------------------------

nux::label*
nux_impl_map (
    nux_label_t* label
) {
    return &label->handle;
}

// Push Button Mappers --------------------------------------------------------

nux::push_button*
nux_impl_map (
    nux_push_button_t* push_button
) {
    return &push_button->handle;
}

// Check Box Mappers ----------------------------------------------------------

nux::check_box*
nux_impl_map (
    nux_check_box_t* check_box
) {
    return &check_box->handle;
}

// Radio Button Mappers -------------------------------------------------------

nux::radio_button*
nux_impl_map (
    nux_radio_button_t* radio_button
) {
    return &radio_button->handle;
}

// Graphics Box Mappers -------------------------------------------------------

nux::graphics_box*
nux_impl_map (
    nux_graphics_box_t* graphics_box
) {
    return &graphics_box->handle;
}

// Group Box Mappers ----------------------------------------------------------

nux::group_box*
nux_impl_map (
    nux_group_box_t* group_box
) {
    return &group_box->handle;
}

// Vector Mappers -------------------------------------------------------------

nux::gvector2d<float>*
nux_impl_map (
    nux_gvector2d_t* gvector2d
) {
    return &gvector2d->handle;
}

nux::gvector3d<float>*
nux_impl_map (
    nux_gvector3d_t* gvector3d
) {
    return &gvector3d->handle;
}

nux::gvector4d<float>*
nux_impl_map (
    nux_gvector4d_t* gvector4d
) {
    return &gvector4d->handle;
}

// Paint Mappers --------------------------------------------------------------

nux::gradient_stop*
nux_impl_map (
    nux_gradient_stop_t* gradient_stop
) {
    return &gradient_stop->handle;
}

nux::paint*
nux_impl_map (
    nux_paint_t* paint
) {
    return &paint->handle;
}

// Vector Path Mappers --------------------------------------------------------

nux::vector_path*
nux_impl_map (
    nux_vector_path_t* vector_path
) {
    return &vector_path->handle;
}

// Window Mode Mappers --------------------------------------------------------

nux::window_mode
nux_impl_map (
    nux_window_mode_t window_mode
) {
    switch (window_mode) {
        case NUXC_WINDOW_MODE_STANDARD: {
            return nux::window_mode::standard;
        }
        case NUXC_WINDOW_MODE_MAXIMIZED: {
            return nux::window_mode::maximized;
        }
        case NUXC_WINDOW_MODE_MINIMIZED: {
            return nux::window_mode::minimized;
        }
    }
}

// Array Mappers --------------------------------------------------------------

template <
    typename Target,
    typename Input
>
std::vector<Target>
nux_impl_map (
    Input** input,
    int input_count
) {
    std::vector<Target> result;
    result.reserve(input_count);
    for (int i{0}; i < input_count; ++i) {
        result.push_back(
            *nux_impl_map(input[i])
        );
    }
    return result;
}

#endif
