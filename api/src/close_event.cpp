// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/close_event.hpp>

#include "system.hpp"

namespace nux {

// ---------------------------------------------------------- nux::close_event

// Constructors and Destructor ------------------------------------------------

close_event::close_event (
    bool initial_should_close
)
noexcept
    : event{event_type::close_event}
    , m_should_close{initial_should_close}
{
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

bool
close_event::should_close ()
const noexcept
{
    return m_should_close;
} // function -----------------------------------------------------------------

void
close_event::set_should_close (
    bool new_value
)
noexcept
{
    m_should_close = new_value;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
