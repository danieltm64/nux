// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/push_button.hpp>

#include "system.hpp"

namespace nux {

// ---------------------------------------------------------- nux::push_button

// Accessors ------------------------------------------------------------------

void
push_button::set_trigger_event_handler (
    const std::function<void()>& new_trigger_event_handler
) {
    m_trigger_event_handler = new_trigger_event_handler;
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

void
push_button::trigger ()
{
    m_trigger_event_handler();
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
