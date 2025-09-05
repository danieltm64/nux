// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/window_element.hpp>

#include "system.hpp"

namespace nux {

// ------------------------------------------------------- nux::window_element

// Constructors and Destructor ------------------------------------------------

window_element::window_element ()
noexcept
    : m_is_dynamically_sized{true}
{
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

alignment
window_element::get_alignment ()
const noexcept
{
    return m_alignment;
} // function -----------------------------------------------------------------

void
window_element::set_alignment (
    alignment new_alignment
) {
    m_alignment = new_alignment;
} // function -----------------------------------------------------------------

size_constraint
window_element::get_size_constraint ()
const noexcept
{
    return m_size_constraint;
} // function -----------------------------------------------------------------

void
window_element::set_size_constraint (
    size_constraint new_size_constraint
) {
    m_size_constraint = new_size_constraint;
} // function -----------------------------------------------------------------

int
window_element::get_x ()
const noexcept
{
    int x;
    int y;
    get_position(x, y);
    return x;
} // function -----------------------------------------------------------------

void
window_element::set_x (
    int new_x
)
noexcept
{
    if (is_geometry_modification_prohibited()) {
        return;
    }
    set_x_forcefully(new_x);
} // function -----------------------------------------------------------------

int
window_element::get_y ()
const noexcept
{
    int x;
    int y;
    get_position(x, y);
    return y;
} // function -----------------------------------------------------------------

void
window_element::set_y (
    int new_y
)
noexcept
{
    if (is_geometry_modification_prohibited()) {
        return;
    }
    set_y_forcefully(new_y);
} // function -----------------------------------------------------------------

void
window_element::set_position (
    int new_x,
    int new_y
)
noexcept
{
    if (is_geometry_modification_prohibited()) {
        return;
    }
    set_position_forcefully(new_x, new_y);
} // function -----------------------------------------------------------------

int
window_element::get_width ()
const noexcept
{
    int width;
    int height;
    get_size(width, height);
    return width;
} // function -----------------------------------------------------------------

void
window_element::set_width (
    int new_width
)
noexcept
{
    if (is_geometry_modification_prohibited()) {
        return;
    }
    set_width_forcefully(new_width);
    handle_resize_event();
} // function -----------------------------------------------------------------

int
window_element::get_height ()
const noexcept
{
    int width;
    int height;
    get_size(width, height);
    return height;
} // function -----------------------------------------------------------------

void
window_element::set_height (
    int new_height
)
noexcept
{
    if (is_geometry_modification_prohibited()) {
        return;
    }
    set_height_forcefully(new_height);
    handle_resize_event();
} // function -----------------------------------------------------------------

void
window_element::set_size (
    int new_width,
    int new_height
)
noexcept
{
    if (is_geometry_modification_prohibited()) {
        return;
    }
    set_size_forcefully(new_width, new_height);
    handle_resize_event();
} // function -----------------------------------------------------------------

int
window_element::get_preferred_width ()
const noexcept
{
    int width;
    int height;
    get_preferred_size(width, height);
    return width;
} // function -----------------------------------------------------------------

int
window_element::get_preferred_height ()
const noexcept
{
    int width;
    int height;
    get_preferred_size(width, height);
    return height;
} // function -----------------------------------------------------------------

int
window_element::get_left_overhead ()
const noexcept
{
    return 0;
} // function -----------------------------------------------------------------

int
window_element::get_right_overhead ()
const noexcept
{
    return 0;
} // function -----------------------------------------------------------------

int
window_element::get_top_overhead ()
const noexcept
{
    return 0;
} // function -----------------------------------------------------------------

int
window_element::get_bottom_overhead ()
const noexcept
{
    return 0;
} // function -----------------------------------------------------------------

int
window_element::get_horizontal_overhead ()
const noexcept
{
    return get_left_overhead() + get_right_overhead();
} // function -----------------------------------------------------------------

int
window_element::get_vertical_overhead ()
const noexcept
{
    return get_top_overhead() + get_bottom_overhead();
} // function -----------------------------------------------------------------


bool
window_element::is_dynamically_sized ()
const noexcept
{
    return m_is_dynamically_sized;
} // function -----------------------------------------------------------------

void
window_element::set_dynamically_sized (
    bool new_dynamically_sized
)
noexcept
{
    m_is_dynamically_sized = new_dynamically_sized;
    if (m_is_dynamically_sized) {
        apply_preferred_size();
    }
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

void
window_element::apply_preferred_size ()
noexcept
{
    int preferred_width;
    int preferred_height;
    get_preferred_size(preferred_width, preferred_height);
    set_size(preferred_width, preferred_height);
} // function -----------------------------------------------------------------

void
window_element::handle_resize_event ()
{
} // function -----------------------------------------------------------------

void
window_element::handle_dpi_update_event (
    int NUX_UNUSED(old_dpi),
    int NUX_UNUSED(new_dpi)
) {
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

void
window_element::set_x_forcefully (
    int new_x
)
noexcept
{
    int current_x;
    int current_y;
    get_position(current_x, current_y);
    set_position_forcefully(new_x, current_y);
} // function -----------------------------------------------------------------

void
window_element::set_y_forcefully (
    int new_y
)
noexcept
{
    int current_x;
    int current_y;
    get_position(current_x, current_y);
    set_position_forcefully(current_x, new_y);
} // function -----------------------------------------------------------------

void
window_element::set_width_forcefully (
    int new_width
)
noexcept
{
    int current_width;
    int current_height;
    get_size(current_width, current_height);
    set_size_forcefully(new_width, current_height);
} // function -----------------------------------------------------------------

void
window_element::set_height_forcefully (
    int new_height
)
noexcept
{
    int current_width;
    int current_height;
    get_size(current_width, current_height);
    set_size_forcefully(current_width, new_height);
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
