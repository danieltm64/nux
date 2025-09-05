// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/event.hpp>

#include "system.hpp"

namespace nux {

// ---------------------------------------------------------------- nux::event

// Constructors and Destructor ------------------------------------------------

event::event (
    event_type initial_event_type
)
noexcept
    : m_event_type{initial_event_type}
{
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

event_type
event::get_event_type ()
const noexcept
{
    return m_event_type;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
