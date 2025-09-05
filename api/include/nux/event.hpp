// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUX_EVENT_HPP_INCLUDED
#define NUX_EVENT_HPP_INCLUDED

#include <nux/core.hpp>

namespace nux {

enum class event_type {
    key_event,
    close_event
}; // enum --------------------------------------------------------------------

class NUX_CONDITIONAL_EXPORT_CLASS event {
public:
    // Constructors and Destructor --------------------------------------------

    NUX_CONDITIONAL_EXPORT
    explicit
    event (
        event_type initial_event_type
    )
    noexcept;

    ~event ()
    = default;

    // Copy Operations --------------------------------------------------------

    event (
        const event& other
    )
    = default;

    event&
    operator = (
        const event& other
    ) &
    = default;

    // Move Operations --------------------------------------------------------

    event (
        event&& other
    )
    noexcept = default;

    event&
    operator = (
        event&& other
    ) &
    noexcept = default;

    // Accessors --------------------------------------------------------------

    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    event_type
    get_event_type ()
    const noexcept;

private:
    event_type m_event_type;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif
