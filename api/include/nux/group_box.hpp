// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUX_GROUP_BOX_HPP_INCLUDED
#define NUX_GROUP_BOX_HPP_INCLUDED

#include <nux/widget.hpp>
#include <nux/layout.hpp>

namespace nux {

class NUX_CONDITIONAL_EXPORT_CLASS group_box
    : public widget
{
public:
    // Constants --------------------------------------------------------------

    static constexpr native_widget_kind g_kind{
        native_widget_kind::group_box
    };

    // Constructors and Destructor --------------------------------------------

    NUX_CONDITIONAL_EXPORT
    explicit
    group_box (
        layout& enclosing_layout
    );

    NUX_CONDITIONAL_EXPORT
    group_box (
        const widget_native_handle& parent_widget_handle,
        layout& enclosing_layout
    );

    ~group_box ()
    noexcept override = default;

    // Accessors --------------------------------------------------------------

    NUX_CONDITIONAL_EXPORT
    layout&
    grab_content_layout ()
    noexcept;

    NUX_CONDITIONAL_EXPORT
    const layout&
    grab_content_layout ()
    const noexcept;

    NUX_CONDITIONAL_EXPORT
    void
    get_preferred_size (
        int& width,
        int& height
    )
    const noexcept override;

    NUX_CONDITIONAL_EXPORT
    int
    get_left_overhead ()
    const noexcept override;

    NUX_CONDITIONAL_EXPORT
    int
    get_right_overhead ()
    const noexcept override;

    NUX_CONDITIONAL_EXPORT
    int
    get_top_overhead ()
    const noexcept override;

    NUX_CONDITIONAL_EXPORT
    int
    get_bottom_overhead ()
    const noexcept override;

    NUX_CONDITIONAL_EXPORT
    nux::string
    get_title ()
    const;

    NUX_CONDITIONAL_EXPORT
    void
    set_title (
        nux::string_view new_title
    );

    // Core -------------------------------------------------------------------

    NUX_CONDITIONAL_EXPORT
    void
    show ()
    noexcept override;

    NUX_CONDITIONAL_EXPORT
    void
    hide ()
    noexcept override;

    template <
        typename Widget,
        typename... Arguments
    >
    requires (std::derived_from<Widget, widget>)
    Widget*
    add_widget (
        Arguments&&... arguments
    ) {
        auto widget_ptr{
            reinterpret_cast<Widget*>(
                m_content_layout.grab_children().emplace_back(
                    std::make_unique<Widget>(
                        grab_native_handle(),
                        m_content_layout,
                        std::forward<Arguments>(arguments)...
                    )
                ).get()
            )
        };
        m_content_layout.update();
        return widget_ptr;
    } // function -------------------------------------------------------------

protected:
    // Protected Functions ----------------------------------------------------

    NUX_CONDITIONAL_EXPORT
    void
    set_size_forcefully (
        int new_width,
        int new_height
    )
    noexcept override;

private:
    // Private Data -----------------------------------------------------------

    layout m_content_layout;

    // Private Functions ------------------------------------------------------

    void
    initialize ()
    noexcept;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif
