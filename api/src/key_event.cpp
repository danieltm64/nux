// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/key_event.hpp>

#include "system.hpp"

namespace nux {

// ------------------------------------------------------------ nux::key_event

// Constructors and Destructor ------------------------------------------------

key_event::key_event (
    key_event_type initial_key_event_type,
    key initial_key
)
noexcept
    : event{event_type::key_event}
    , m_key_event_type{initial_key_event_type}
    , m_key{initial_key}
{
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

key_event_type
key_event::get_key_event_type ()
const noexcept
{
    return m_key_event_type;
} // function -----------------------------------------------------------------

key
key_event::get_key ()
const noexcept
{
    return m_key;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
