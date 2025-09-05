// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <iostream>
#include <nux/window.hpp>

#include <nux/group_box.hpp>

#include "system.hpp"

namespace nux {

namespace impl {

void
update_window (
    window* w
) {
    std::chrono::steady_clock::time_point current_time{
        std::chrono::steady_clock::now()
    };
    std::chrono::duration<double> difference{
        std::chrono::duration_cast<
            std::chrono::duration<double>
        >(current_time - w->m_last_time)
    };
    const double delta_seconds{difference.count()};

    w->m_last_time = current_time;
    difference = std::chrono::duration_cast<
        std::chrono::duration<double>
    >(current_time - w->m_start_time);
    const double total_seconds{difference.count()};

    w->update(delta_seconds, total_seconds);
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

// --------------------------------------------------------------- nux::window

// Constructors and Destructor ------------------------------------------------

window::~window ()
noexcept
{
    if (app()->is_running()) {
        close();
    }
    delete m_native_handle;
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

window_native_handle&
window::grab_native_handle ()
noexcept
{
    return *m_native_handle;
} // function -----------------------------------------------------------------

const window_native_handle&
window::grab_native_handle ()
const noexcept
{
    return *m_native_handle;
} // function -----------------------------------------------------------------

layout&
window::grab_root_layout ()
noexcept
{
    return m_root_layout;
} // function -----------------------------------------------------------------

const layout&
window::grab_root_layout ()
const noexcept
{
    return m_root_layout;
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

void
window::update (
    double NUX_UNUSED(delta_seconds),
    double NUX_UNUSED(total_seconds)
) {
    render_graphics_boxes(grab_root_layout().grab_children());
} // function -----------------------------------------------------------------

void
window::handle_key_down_event (
    key_event& NUX_UNUSED(ev)
) {
} // function -----------------------------------------------------------------

void
window::handle_key_up_event (
    key_event& NUX_UNUSED(ev)
) {
} // function -----------------------------------------------------------------

void
window::handle_resize_event ()
{
} // function -----------------------------------------------------------------

void
window::handle_close_event (
    close_event& NUX_UNUSED(ev)
) {
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

void
window::update_root_layout ()
noexcept
{
    if (!m_root_layout.is_empty()) {
        int width;
        int height;
        get_size(width, height);
        m_root_layout.set_size(width, height);
    }
} // function -----------------------------------------------------------------

void
window::render_graphics_boxes (
    std::vector<std::unique_ptr<window_element>>& window_elements
) {
    for (auto& current_window_element : window_elements) {
        auto graphics_box_ptr{
            dynamic_cast<graphics_box*>(current_window_element.get())
        };
        if (graphics_box_ptr) {
            graphics_box_ptr->render();
            continue;
        }
        auto group_box_ptr{
            dynamic_cast<group_box*>(current_window_element.get())
        };
        if (group_box_ptr) {
            render_graphics_boxes(
                group_box_ptr->grab_content_layout().grab_children()
            );
        }
        auto layout_ptr{dynamic_cast<layout*>(current_window_element.get())};
        if (layout_ptr) {
            render_graphics_boxes(layout_ptr->grab_children());
        }
    }
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
