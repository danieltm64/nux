// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUX_CLOSE_EVENT_HPP_INCLUDED
#define NUX_CLOSE_EVENT_HPP_INCLUDED

#include <nux/event.hpp>

namespace nux {

class NUX_CONDITIONAL_EXPORT_CLASS close_event
    : public event
{
public:
    // Constructors and Destructor --------------------------------------------

    NUX_CONDITIONAL_EXPORT
    explicit
    close_event (
        bool initial_should_close
    )
    noexcept;

    ~close_event ()
    = default;

    // Copy Operations --------------------------------------------------------

    close_event (
        const close_event& other
    )
    = default;

    close_event&
    operator = (
        const close_event& other
    ) &
    = default;

    // Move Operations --------------------------------------------------------

    close_event (
        close_event&& other
    )
    noexcept = default;

    close_event&
    operator = (
        close_event&& other
    ) &
    noexcept = default;

    // Accessors --------------------------------------------------------------

    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    bool
    should_close ()
    const noexcept;

    NUX_CONDITIONAL_EXPORT
    void
    set_should_close (
        bool new_value
    )
    noexcept;

private:
    // Private Data -----------------------------------------------------------

    bool m_should_close;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif
