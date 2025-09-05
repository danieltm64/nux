// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUX_KEY_EVENT_HPP_INCLUDED
#define NUX_KEY_EVENT_HPP_INCLUDED

#include <nux/event.hpp>
#include <nux/general.hpp>

namespace nux {

enum class key_event_type {
    key_down,
    key_up
}; // enum --------------------------------------------------------------------

class NUX_CONDITIONAL_EXPORT_CLASS key_event
    : public event
{
public:
    // Constructors and Destructor --------------------------------------------

    NUX_CONDITIONAL_EXPORT
    key_event (
        key_event_type initial_key_event_type,
        key initial_key
    )
    noexcept;

    ~key_event ()
    = default;

    // Copy Operations --------------------------------------------------------

    key_event (
        const key_event& other
    )
    = default;

    key_event&
    operator = (
        const key_event& other
    ) &
    = default;

    // Move Operations --------------------------------------------------------

    key_event (
        key_event&& other
    )
    noexcept = default;

    key_event&
    operator = (
        key_event&& other
    ) &
    noexcept = default;

    // Accessors --------------------------------------------------------------

    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    key_event_type
    get_key_event_type ()
    const noexcept;

    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    key
    get_key ()
    const noexcept;

private:
    // Private Data -----------------------------------------------------------

    key_event_type m_key_event_type;
    key m_key;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif
