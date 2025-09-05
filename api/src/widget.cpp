// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/widget.hpp>

#include "system.hpp"

namespace nux {

// Constructors and Destructor ------------------------------------------------

widget::~widget ()
noexcept
{
    delete m_native_handle;
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

widget_native_handle&
widget::grab_native_handle ()
noexcept
{
    return *m_native_handle;
} // function -----------------------------------------------------------------

const widget_native_handle&
widget::grab_native_handle ()
const noexcept
{
    return *m_native_handle;
} // function -----------------------------------------------------------------

layout&
widget::grab_enclosing_layout ()
noexcept
{
    return *m_enclosing_layout;
} // function -----------------------------------------------------------------

const layout&
widget::grab_enclosing_layout ()
const noexcept
{
    return *m_enclosing_layout;
} // function -----------------------------------------------------------------

void
widget::set_x (
    int new_x
)
noexcept
{
    const auto& enclosing_layout{grab_enclosing_layout()};
    window_element::set_x(new_x + enclosing_layout.get_left_margin());
} // function -----------------------------------------------------------------

void
widget::set_y (
    int new_y
)
noexcept
{
    const auto& enclosing_layout{grab_enclosing_layout()};
    window_element::set_y(new_y + enclosing_layout.get_top_margin());
} // function -----------------------------------------------------------------

void
widget::set_position (
    int new_x,
    int new_y
)
noexcept
{
    const auto& enclosing_layout{grab_enclosing_layout()};
    window_element::set_position(
        new_x + enclosing_layout.get_left_margin(),
        new_y + enclosing_layout.get_top_margin()
    );
} // function -----------------------------------------------------------------

// Protected Functions --------------------------------------------------------

bool
widget::is_geometry_modification_prohibited ()
const noexcept
{
    return m_enclosing_layout->get_kind() != layout::kind::fixed;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
