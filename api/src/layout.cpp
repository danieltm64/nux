// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/layout.hpp>

#include "system.hpp"

namespace nux {

// --------------------------------------------------------------- nux::layout

// Constructors and Destructor ------------------------------------------------

layout::layout (
    window_native_handle* initial_enclosing_window_handle
)
noexcept
    : m_parent{nullptr}
    , m_native_handle{nullptr}
    , m_enclosing_window_handle{initial_enclosing_window_handle}
    , m_kind{kind::flow}
    , m_axis{axis::vertical}
    , m_direction{direction::forward}
    , m_x{0}
    , m_y{0}
    , m_width{0}
    , m_height{0}
    , m_left_margin{0}
    , m_top_margin{0}
    , m_right_margin{0}
    , m_bottom_margin{0}
    , m_horizontal_padding{0}
    , m_vertical_padding{0}
    , m_children{}
{
} // function -----------------------------------------------------------------

layout::layout (
    layout& parent,
    kind initial_kind,
    axis initial_axis,
    direction initial_direction
)
noexcept
    : m_parent{&parent}
    , m_native_handle{nullptr}
    , m_enclosing_window_handle{parent.m_enclosing_window_handle}
    , m_kind{initial_kind}
    , m_axis{initial_axis}
    , m_direction{initial_direction}
    , m_x{0}
    , m_y{0}
    , m_width{0}
    , m_height{0}
    , m_left_margin{0}
    , m_top_margin{0}
    , m_right_margin{0}
    , m_bottom_margin{0}
    , m_horizontal_padding{0}
    , m_vertical_padding{0}
    , m_children{}
{
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

layout&
layout::grab_parent ()
noexcept
{
    return *m_parent;
} // function -----------------------------------------------------------------

const layout&
layout::grab_parent ()
const noexcept
{
    return *m_parent;
} // function -----------------------------------------------------------------

layout_native_handle&
layout::grab_native_handle ()
noexcept
{
    return *m_native_handle;
} // function -----------------------------------------------------------------

const layout_native_handle&
layout::grab_native_handle ()
const noexcept
{
    return *m_native_handle;
} // function -----------------------------------------------------------------

window_native_handle&
layout::grab_enclosing_window_handle ()
noexcept
{
    return *m_enclosing_window_handle;
} // function -----------------------------------------------------------------

const window_native_handle&
layout::grab_enclosing_window_handle ()
const noexcept
{
    return *m_enclosing_window_handle;
} // function -----------------------------------------------------------------

std::vector<std::unique_ptr<window_element>>&
layout::grab_children ()
noexcept
{
    return m_children;
} // function -----------------------------------------------------------------

const std::vector<std::unique_ptr<window_element>>&
layout::grab_children ()
const noexcept
{
    return m_children;
} // function -----------------------------------------------------------------

layout::kind
layout::get_kind ()
const noexcept
{
    return m_kind;
} // function -----------------------------------------------------------------

layout::axis
layout::get_axis ()
const noexcept
{
    return m_axis;
} // function -----------------------------------------------------------------

layout::direction
layout::get_direction ()
const noexcept
{
    return m_direction;
} // function -----------------------------------------------------------------

void
layout::set_x (
    int new_x
)
noexcept
{
    if (m_parent) {
        new_x += m_parent->get_left_margin();
    }
    window_element::set_x(new_x);
} // function -----------------------------------------------------------------

void
layout::set_y (
    int new_y
)
noexcept
{
    if (m_parent) {
        new_y += m_parent->get_top_margin();
    }
    window_element::set_y(new_y);
} // function -----------------------------------------------------------------

void
layout::get_position (
    int& x,
    int& y
)
const noexcept
{
    x = m_x;
    y = m_y;
} // function -----------------------------------------------------------------

void
layout::set_position (
    int new_x,
    int new_y
)
noexcept
{
    if (m_parent) {
        new_x += m_parent->get_left_margin();
        new_y += m_parent->get_top_margin();
    }
    window_element::set_position(new_x, new_y);
} // function -----------------------------------------------------------------

void
layout::get_size (
    int& width,
    int& height
)
const noexcept
{
    width = m_width;
    height = m_height;
} // function -----------------------------------------------------------------

void
layout::set_size (
    int new_width,
    int new_height
)
noexcept
{
    window_element::set_size(new_width, new_height);
} // function -----------------------------------------------------------------

int
layout::get_preferred_width ()
const noexcept
{
    if (m_axis == axis::vertical) {
        int width{0};
        for (const auto& current_child : m_children) {
            width = std::max<int>(
                width,
                current_child->get_preferred_width()
            );
        }
        width += m_left_margin + m_right_margin;
        return width;
    } else {
        int width{m_left_margin + m_right_margin};
        for (const auto& current_child : m_children) {
            width += current_child->get_preferred_width();
        }
        return width;
    }
} // function -----------------------------------------------------------------

int
layout::get_preferred_height ()
const noexcept
{
    if (m_axis == axis::vertical) {
        int height{m_top_margin + m_bottom_margin};
        for (const auto& current_child : m_children) {
            height += current_child->get_preferred_height();
        }
        return height;
    } else {
        int height{0};
        for (const auto& current_child : m_children) {
            height = std::max<int>(
                height,
                current_child->get_preferred_height()
            );
        }
        height += m_top_margin + m_bottom_margin;
        return height;
    }
} // function -----------------------------------------------------------------

void
layout::get_preferred_size (
    int& width,
    int& height
)
const noexcept
{
    width = get_preferred_width();
    height = get_preferred_height();
} // function -----------------------------------------------------------------

bool
layout::is_empty ()
const noexcept
{
    return m_children.empty();
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

layout*
layout::add_layout (
    kind initial_kind,
    axis initial_axis,
    direction initial_direction
) {
    auto layout_pointer{
        reinterpret_cast<layout*>(
            m_children.emplace_back(
                std::make_unique<layout>(
                    *this,
                    initial_kind,
                    initial_axis,
                    initial_direction
                )
            ).get()
        )
    };
    update();
    return layout_pointer;
} // function -----------------------------------------------------------------

void
layout::show ()
noexcept
{
    for (auto& current_child : m_children) {
        current_child->show();
    }
} // function -----------------------------------------------------------------

void
layout::hide ()
noexcept
{
    for (auto& current_child : m_children) {
        current_child->hide();
    }
} // function -----------------------------------------------------------------

void
layout::update ()
noexcept
{
    update_layout_horizontally();
    update_layout_vertically();
} // function -----------------------------------------------------------------

void
layout::handle_dpi_update_event (
    int old_dpi,
    int new_dpi
) {
    for (auto& current_child : m_children) {
        current_child->handle_dpi_update_event(old_dpi, new_dpi);
    }
} // function -----------------------------------------------------------------

// Protected Functions --------------------------------------------------------

layout::layout (
    window_native_handle& enclosing_window_handle,
    kind initial_kind,
    axis initial_axis,
    direction initial_direction
)
noexcept
    : m_parent{nullptr}
    , m_native_handle{nullptr}
    , m_enclosing_window_handle{&enclosing_window_handle}
    , m_kind{initial_kind}
    , m_axis{initial_axis}
    , m_direction{initial_direction}
    , m_x{0}
    , m_y{0}
    , m_width{0}
    , m_height{0}
    , m_left_margin{0}
    , m_top_margin{0}
    , m_right_margin{0}
    , m_bottom_margin{0}
    , m_horizontal_padding{0}
    , m_vertical_padding{0}
{
} // function -----------------------------------------------------------------

bool
layout::is_geometry_modification_prohibited ()
const noexcept
{
    if (m_parent) {
        return m_parent->m_kind != layout::kind::fixed;
    }
    return false;
} // function -----------------------------------------------------------------

void
layout::set_position_forcefully (
    int new_x,
    int new_y
)
noexcept
{
    if (m_x != new_x) {
        int delta_x{new_x - m_x};
        for (auto& current_child : m_children) {
            current_child->set_x_forcefully(current_child->get_x() + delta_x);
        }
        m_x = new_x;
        update_layout_horizontally();
    }
    if (m_y != new_y) {
        int delta_y{new_y - m_y};
        for (auto& current_child : m_children) {
            current_child->set_y_forcefully(current_child->get_y() + delta_y);
        }
        m_y = new_y;
        update_layout_vertically();
    }
} // function -----------------------------------------------------------------

void
layout::set_size_forcefully (
    int new_width,
    int new_height
)
noexcept
{
    if (m_width != new_width) {
        m_width = new_width;
        update_layout_horizontally();
    }
    if (m_height != new_height) {
        m_height = new_height;
        update_layout_vertically();
    }
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

int
layout::get_left_margin ()
const noexcept
{
    return m_left_margin;
} // function -----------------------------------------------------------------

void
layout::set_left_margin (
    int new_left_margin
)
noexcept
{
    if (m_left_margin != new_left_margin) {
        m_left_margin = new_left_margin;
        update_layout_horizontally();
    }
} // function -----------------------------------------------------------------

int
layout::get_top_margin ()
const noexcept
{
    return m_top_margin;
} // function -----------------------------------------------------------------

void
layout::set_top_margin (
    int new_top_margin
)
noexcept
{
    if (m_top_margin != new_top_margin) {
        m_top_margin = new_top_margin;
        update_layout_vertically();
    }
} // function -----------------------------------------------------------------

int
layout::get_right_margin ()
const noexcept
{
    return m_right_margin;
} // function -----------------------------------------------------------------

void
layout::set_right_margin (
    int new_right_margin
)
noexcept
{
    if (m_right_margin != new_right_margin) {
        m_right_margin = new_right_margin;
        update_layout_horizontally();
    }
} // function -----------------------------------------------------------------

int
layout::get_bottom_margin ()
const noexcept
{
    return m_bottom_margin;
} // function -----------------------------------------------------------------

void
layout::set_bottom_margin (
    int new_bottom_margin
)
noexcept
{
    if (m_bottom_margin != new_bottom_margin) {
        m_bottom_margin = new_bottom_margin;
        update_layout_vertically();
    }
} // function -----------------------------------------------------------------

int
layout::get_horizontal_padding ()
const noexcept
{
    return m_horizontal_padding;
} // function -----------------------------------------------------------------

void
layout::set_horizontal_padding (
    int new_horizontal_padding
)
noexcept
{
    m_horizontal_padding = new_horizontal_padding;
} // function -----------------------------------------------------------------

int
layout::get_vertical_padding ()
const noexcept
{
    return m_vertical_padding;
} // function -----------------------------------------------------------------

void
layout::set_vertical_padding (
    int new_vertical_padding
)
noexcept
{
    m_vertical_padding = new_vertical_padding;
} // function -----------------------------------------------------------------

void
layout::update_layout_horizontally ()
noexcept
{
#if !defined(NUX_OS_LINUX_BASED)
    if (m_kind == kind::fixed || m_children.empty()) {
        return;
    }

    if (m_parent == nullptr) {
        m_x = 0;
    }

    if (m_axis == axis::horizontal) {
        const int equal_share{
            std::max<int>(
                0,
                (m_width - m_left_margin - m_right_margin - m_horizontal_padding) / m_children.size()
            )
        };
        int current_x{m_x + m_left_margin};
        if (m_direction == direction::forward) {
            for (auto& current_child : m_children) {
                current_child->set_width_forcefully(equal_share);
                current_child->set_x_forcefully(current_x);
                current_x += equal_share;
            }
        } else {
            for (auto& current_child : std::ranges::reverse_view{m_children}) {
                current_child->set_width_forcefully(equal_share);
                current_child->set_x_forcefully(current_x);
                current_x += equal_share;
            }
        }
    } else {
        const int width{
            std::max<int>(
                0,
                m_width - m_left_margin - m_right_margin - m_horizontal_padding
            )
        };
        const int x{m_x + m_left_margin};
        for (auto& current_child : m_children) {
            current_child->set_width_forcefully(width);
            current_child->set_x_forcefully(x);
        }
    }
#endif
} // function -----------------------------------------------------------------

void
layout::update_layout_vertically ()
noexcept
{
#if !defined(NUX_OS_LINUX_BASED)
    if (m_kind == kind::fixed || m_children.empty()) {
        return;
    }

    if (m_parent == nullptr) {
        m_y = 0;
    }

    if (m_axis == axis::vertical) {
        const int equal_share{
            std::max<int>(
                0,
                (m_height - m_top_margin - m_bottom_margin - m_vertical_padding) / m_children.size()
            )
        };
        int current_y{m_y + m_top_margin};
        if (m_direction == direction::forward) {
            for (auto& current_child : m_children) {
                current_child->set_height_forcefully(equal_share);
                current_child->set_y_forcefully(current_y);
                current_y += equal_share;
            }
        } else {
            for (auto& current_child : std::ranges::reverse_view{m_children}) {
                current_child->set_height_forcefully(equal_share);
                current_child->set_y_forcefully(current_y);
                current_y += equal_share;
            }
        }
    } else {
        const int height{
            std::max<int>(
                0,
                m_height - m_top_margin - m_bottom_margin - m_vertical_padding
            )
        };
        const int y{m_y + m_top_margin};
        for (auto& current_child : m_children) {
            current_child->set_height_forcefully(height);
            current_child->set_y_forcefully(y);
        }
    }
#endif
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
