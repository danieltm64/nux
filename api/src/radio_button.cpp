// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/radio_button.hpp>

#include "system.hpp"

namespace nux {

// --------------------------------------------------------- nux::radio_button

// Accessors ------------------------------------------------------------------

const check_group<radio_button>&
radio_button::grab_group ()
const noexcept
{
    return m_group;
} // function -----------------------------------------------------------------

check_group<radio_button>&
radio_button::grab_group ()
noexcept
{
    return m_group;
} // function -----------------------------------------------------------------

void
radio_button::set_toggle_event_handler (
    const std::function<void()>& new_toggle_event_handler
) {
    m_toggle_event_handler = new_toggle_event_handler;
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

void
radio_button::toggle ()
{
    m_group.set_active_element(*this);
    m_toggle_event_handler();
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
