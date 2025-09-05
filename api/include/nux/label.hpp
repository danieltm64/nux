// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUX_LABEL_HPP_INCLUDED
#define NUX_LABEL_HPP_INCLUDED

#include <nux/widget.hpp>

namespace nux {

class NUX_CONDITIONAL_EXPORT_CLASS label
    : public widget
{
public:
    // Constants --------------------------------------------------------------

    static constexpr native_widget_kind g_kind{
        native_widget_kind::label
    };

    // Constructors and Destructor --------------------------------------------

    NUX_CONDITIONAL_EXPORT
    explicit
    label (
        layout& enclosing_layout
    );

    NUX_CONDITIONAL_EXPORT
    label (
        const widget_native_handle& parent_widget_handle,
        layout& enclosing_layout
    );

    ~label ()
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
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif
