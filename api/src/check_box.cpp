// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/check_box.hpp>

#include "system.hpp"

namespace nux {

// ------------------------------------------------------------ nux::check_box

// Accessors ------------------------------------------------------------------

void
check_box::set_toggle_event_handler (
    const std::function<void()>& new_toggle_event_handler
) {
    m_toggle_event_handler = new_toggle_event_handler;
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

void
check_box::toggle ()
{
    m_toggle_event_handler();
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
