// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/layout.hpp>

#include "qt.hpp"

namespace nux {

// --------------------------------------------------------------- nux::layout

// Accessors ------------------------------------------------------------------

void
layout::set_kind (
    kind new_kind
)
noexcept
{
    if (m_kind != new_kind) {
        m_kind = new_kind;
        update();
    }
} // function -----------------------------------------------------------------

void
layout::set_axis (
    axis new_axis
)
noexcept
{
    if (m_axis != new_axis) {
        m_axis = new_axis;
        update();
    }
} // function -----------------------------------------------------------------

void
layout::set_direction (
    direction new_direction
)
noexcept
{
    if (m_direction != new_direction) {
        m_direction = new_direction;
        if (m_axis == axis::horizontal) {
            update_layout_horizontally();
        } else {
            update_layout_vertically();
        }
    }
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
