// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUX_PUSH_BUTTON_HPP_INCLUDED
#define NUX_PUSH_BUTTON_HPP_INCLUDED

#include <nux/widget.hpp>

namespace nux {

class NUX_CONDITIONAL_EXPORT_CLASS push_button
    : public widget
{
public:
    // Constants --------------------------------------------------------------

    static constexpr native_widget_kind g_kind{
        native_widget_kind::push_button
    };

    // Constructors and Destructor --------------------------------------------

    NUX_CONDITIONAL_EXPORT
    explicit
    push_button (
        layout& enclosing_layout
    );

    NUX_CONDITIONAL_EXPORT
    push_button (
        const widget_native_handle& parent_widget_handle,
        layout& enclosing_layout
    );

    ~push_button ()
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
    void
    set_trigger_event_handler (
        const std::function<void()>& new_trigger_event_handler
    );

    // Core -------------------------------------------------------------------

    NUX_CONDITIONAL_EXPORT
    void
    trigger ();

private:
    // Private Data -----------------------------------------------------------

    std::function<void()> m_trigger_event_handler;

    // Private Functions ------------------------------------------------------

    void
    initialize ();
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif
