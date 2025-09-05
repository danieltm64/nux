// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUX_RADIO_BUTTON_HPP_INCLUDED
#define NUX_RADIO_BUTTON_HPP_INCLUDED

#include <nux/widget.hpp>
#include <nux/check_group.hpp>

namespace nux {

class NUX_CONDITIONAL_EXPORT_CLASS radio_button
    : public widget
{
public:
    // Constants --------------------------------------------------------------

    static constexpr native_widget_kind g_kind{
        native_widget_kind::radio_button
    };

    // Constructors and Destructor --------------------------------------------

    NUX_CONDITIONAL_EXPORT
    explicit
    radio_button (
        layout& enclosing_layout,
        check_group<radio_button>& group
    );

    NUX_CONDITIONAL_EXPORT
    radio_button (
        const widget_native_handle& parent_widget_handle,
        layout& enclosing_layout,
        check_group<radio_button>& group
    );

    ~radio_button ()
    noexcept override = default;

    // Accessors --------------------------------------------------------------

    NUX_CONDITIONAL_EXPORT
    void
    get_preferred_size (
        int& width,
        int& height
    )
    const noexcept override;

    NUX_CONDITIONAL_EXPORT
    nux::string
    get_text ()
    const;

    NUX_CONDITIONAL_EXPORT
    void
    set_text (
        nux::string_view new_text
    );

    NUX_CONDITIONAL_EXPORT
    bool
    is_checked ();

    NUX_CONDITIONAL_EXPORT
    void
    set_checked (
        bool new_checked
    );

    NUX_CONDITIONAL_EXPORT
    const check_group<radio_button>&
    grab_group ()
    const noexcept;

    NUX_CONDITIONAL_EXPORT
    check_group<radio_button>&
    grab_group ()
    noexcept;

    NUX_CONDITIONAL_EXPORT
    void
    set_toggle_event_handler (
        const std::function<void()>& new_toggle_event_handler
    );

    // Core -------------------------------------------------------------------

    NUX_CONDITIONAL_EXPORT
    void
    toggle ();

private:
    // Private Data -----------------------------------------------------------

    check_group<radio_button>& m_group;
    std::function<void()> m_toggle_event_handler;

    // Private Functions ------------------------------------------------------

    void
    initialize ();
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif
