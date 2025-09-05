// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/graphics_box.hpp>

#include "system.hpp"

namespace nux {

// --------------------------------------------------------- nux::graphics_box

// Accessors ------------------------------------------------------------------

void
graphics_box::get_preferred_size (
    int& width,
    int& height
)
const noexcept
{
    width = 0;
    height = 0;
} // function -----------------------------------------------------------------

void
graphics_box::set_render_event_handler (
    const std::function<void()>& new_render_event_handler
)
noexcept
{
    m_render_event_handler = new_render_event_handler;
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

void
graphics_box::fill_path (
    const vector_path& path,
    const paint& fill_paint
) {
    render_path(path, fill_paint, true);
} // function -----------------------------------------------------------------

void
graphics_box::stroke_path (
    const vector_path& path,
    const paint& stroke_paint
) {
    render_path(path, stroke_paint, false);
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
