// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUX_WIDGET_HPP_INCLUDED
#define NUX_WIDGET_HPP_INCLUDED

#include <nux/widget_native_handle.hpp>
#include <nux/layout.hpp>

#include <cmath>
#include <functional>
#include <utility>

namespace nux {

enum class native_widget_kind {
    label,
    push_button,
    check_box,
    radio_button,
    group_box,
    graphics_box
}; // enum --------------------------------------------------------------------

namespace impl {

template <
    typename... Args
>
void
noop (
    Args... NUX_UNUSED(args)
)
noexcept
{
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

class NUX_CONDITIONAL_EXPORT_CLASS widget
    : public window_element
{
public:
    // Constructors and Destructor --------------------------------------------

    NUX_CONDITIONAL_EXPORT
    explicit
    widget (
        layout& enclosing_layout
    );

    NUX_CONDITIONAL_EXPORT
    ~widget ()
    noexcept override;

    // Accessors --------------------------------------------------------------

    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    widget_native_handle&
    grab_native_handle ()
    noexcept;

    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const widget_native_handle&
    grab_native_handle ()
    const noexcept;

    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    layout&
    grab_enclosing_layout ()
    noexcept;

    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const layout&
    grab_enclosing_layout ()
    const noexcept;

    NUX_CONDITIONAL_EXPORT
    void
    set_x (
        int new_x
    )
    noexcept override;

    NUX_CONDITIONAL_EXPORT
    void
    set_y (
        int new_y
    )
    noexcept override;

    NUX_CONDITIONAL_EXPORT
    void
    get_position (
        int& x,
        int& y
    )
    const noexcept override;

    NUX_CONDITIONAL_EXPORT
    void
    set_position (
        int new_x,
        int new_y
    )
    noexcept override;

    NUX_CONDITIONAL_EXPORT
    void
    get_size (
        int& width,
        int& height
    )
    const noexcept override;

    NUX_CONDITIONAL_EXPORT
    bool
    is_enabled ()
    const noexcept;

    NUX_CONDITIONAL_EXPORT
    void
    set_enabled (
        bool new_enabled
    )
    noexcept;

    // Core -------------------------------------------------------------------

    NUX_CONDITIONAL_EXPORT
    void
    show ()
    noexcept override;

    NUX_CONDITIONAL_EXPORT
    void
    hide ()
    noexcept override;

    NUX_CONDITIONAL_EXPORT
    void
    handle_dpi_update_event (
        int old_dpi,
        int new_dpi
    )
    override;

    // Friends ----------------------------------------------------------------

    friend class layout;

protected:
    // Protected Functions ----------------------------------------------------

    NUX_CONDITIONAL_EXPORT
    explicit
    widget (
        layout& enclosing_layout,
        widget_native_handle&& widget_handle
    );

    NUX_CONDITIONAL_EXPORT
    bool
    is_geometry_modification_prohibited ()
    const noexcept override;

    NUX_CONDITIONAL_EXPORT
    void
    set_position_forcefully (
        int new_x,
        int new_y
    )
    noexcept override;

    NUX_CONDITIONAL_EXPORT
    void
    set_size_forcefully (
        int new_width,
        int new_height
    )
    noexcept override;

#if defined(NUX_OS_MACOS) || defined(NUX_OS_LINUX_BASED)
    static
    void
    get_preferred_size_generically (
        const widget_native_handle& native_handle,
        int& width,
        int& height
    )
    noexcept;
#endif

#if defined(NUX_OS_WINDOWS) || defined(NUX_OS_MACOS)
    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    int
    get_parent_dpi ()
    const noexcept;
#endif

private:
    // Private Data -----------------------------------------------------------

    widget_native_handle* m_native_handle;
    layout* m_enclosing_layout;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif
