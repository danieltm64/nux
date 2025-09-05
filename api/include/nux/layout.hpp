// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUX_LAYOUT_HPP_INCLUDED
#define NUX_LAYOUT_HPP_INCLUDED

#include <concepts>
#include <vector>
#include <memory>
#include <numeric>
#include <ranges>
#include <algorithm>

#include <nux/window_native_handle.hpp>
#include <nux/layout_native_handle.hpp>
#include <nux/window_element.hpp>

namespace nux {

class widget;
class group_box;

class NUX_CONDITIONAL_EXPORT_CLASS layout
    : public window_element
{
public:
    // Types ------------------------------------------------------------------

    enum class kind {
        fixed,
        flow
    }; // enum ----------------------------------------------------------------

    enum class axis {
        horizontal,
        vertical
    }; // enum ----------------------------------------------------------------

    enum class direction {
        forward,
        reverse
    }; // enum ----------------------------------------------------------------

    // Constructors and Destructor --------------------------------------------

    NUX_CONDITIONAL_EXPORT
    layout (
        window_native_handle* initial_enclosing_window_handle = nullptr
    )
    noexcept;

    NUX_CONDITIONAL_EXPORT
    layout (
        layout& parent,
        kind initial_kind,
        axis initial_axis,
        direction initial_direction
    )
    noexcept;

    ~layout ()
    noexcept override = default;

    // Copy Operations --------------------------------------------------------

    layout (
        const layout& other
    ) = delete;

    layout&
    operator = (
        const layout& other
    ) & = delete;

    // Move Operations --------------------------------------------------------

    layout (
        layout&& other
    )
    noexcept = default;

    layout&
    operator = (
        layout&& other
    ) &
    noexcept = default;

    // Accessors --------------------------------------------------------------

    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    layout&
    grab_parent ()
    noexcept;

    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const layout&
    grab_parent ()
    const noexcept;

    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    layout_native_handle&
    grab_native_handle ()
    noexcept;

    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const layout_native_handle&
    grab_native_handle ()
    const noexcept;

    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    window_native_handle&
    grab_enclosing_window_handle ()
    noexcept;

    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const window_native_handle&
    grab_enclosing_window_handle ()
    const noexcept;

    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    std::vector<std::unique_ptr<window_element>>&
    grab_children ()
    noexcept;

    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    const std::vector<std::unique_ptr<window_element>>&
    grab_children ()
    const noexcept;

    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    kind
    get_kind ()
    const noexcept;

    NUX_CONDITIONAL_EXPORT
    void
    set_kind (
        kind new_kind
    )
    noexcept;

    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    axis
    get_axis ()
    const noexcept;

    NUX_CONDITIONAL_EXPORT
    void
    set_axis (
        axis new_axis
    )
    noexcept;

    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    direction
    get_direction ()
    const noexcept;

    NUX_CONDITIONAL_EXPORT
    void
    set_direction (
        direction new_direction
    )
    noexcept;

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
    void
    set_size (
        int new_width,
        int new_height
    )
    noexcept override;

    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    int
    get_preferred_width ()
    const noexcept override;

    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    int
    get_preferred_height ()
    const noexcept override;

    NUX_CONDITIONAL_EXPORT
    void
    get_preferred_size (
        int& width,
        int& height
    )
    const noexcept override;

    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    bool
    is_empty ()
    const noexcept;

    // Core -------------------------------------------------------------------

    template <
        typename Widget,
        typename... Arguments
    >
    requires (std::derived_from<Widget, widget>)
    Widget*
    add_widget (
        Arguments&&... arguments
    ) {
        auto widget_pointer{
            reinterpret_cast<Widget*>(
                m_children.emplace_back(
                    std::make_unique<Widget>(
                        *this,
                        std::forward<Arguments>(arguments)...
                    )
                ).get()
            )
        };
        update();
        return widget_pointer;
    } // function -------------------------------------------------------------

    NUX_CONDITIONAL_EXPORT
    layout*
    add_layout (
        kind initial_kind,
        axis initial_axis,
        direction initial_direction
    );

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
    update ()
    noexcept;

    NUX_CONDITIONAL_EXPORT
    void
    handle_dpi_update_event (
        int old_dpi,
        int new_dpi
    )
    override;

    // Friends ----------------------------------------------------------------

    friend class window;
    friend class widget;
    friend class group_box;

protected:
    // Protected Functions ----------------------------------------------------

    NUX_CONDITIONAL_EXPORT
    layout (
        window_native_handle& enclosing_window_handle,
        kind initial_kind,
        axis initial_axis,
        direction initial_direction
    )
    noexcept;

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

private:
    // Private Data -----------------------------------------------------------

    layout* m_parent;
    layout_native_handle* m_native_handle;
    window_native_handle* m_enclosing_window_handle;
    kind m_kind;
    axis m_axis;
    direction m_direction;
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    int m_left_margin;
    int m_top_margin;
    int m_right_margin;
    int m_bottom_margin;
    int m_horizontal_padding;
    int m_vertical_padding;
    std::vector<std::unique_ptr<window_element>> m_children;

    // Private Functions ------------------------------------------------------

    NUX_CONDITIONAL_EXPORT
    int
    get_left_margin ()
    const noexcept;

    NUX_CONDITIONAL_EXPORT
    void
    set_left_margin (
        int new_left_margin
    )
    noexcept;

    NUX_CONDITIONAL_EXPORT
    int
    get_top_margin ()
    const noexcept;

    NUX_CONDITIONAL_EXPORT
    void
    set_top_margin (
        int new_top_margin
    )
    noexcept;

    NUX_CONDITIONAL_EXPORT
    int
    get_right_margin ()
    const noexcept;

    NUX_CONDITIONAL_EXPORT
    void
    set_right_margin (
        int new_right_margin
    )
    noexcept;

    NUX_CONDITIONAL_EXPORT
    int
    get_bottom_margin ()
    const noexcept;

    NUX_CONDITIONAL_EXPORT
    void
    set_bottom_margin (
        int new_bottom_margin
    )
    noexcept;

    NUX_CONDITIONAL_EXPORT
    int
    get_horizontal_padding ()
    const noexcept;

    NUX_CONDITIONAL_EXPORT
    void
    set_horizontal_padding (
        int new_horizontal_padding
    )
    noexcept;

    NUX_CONDITIONAL_EXPORT
    int
    get_vertical_padding ()
    const noexcept;

    NUX_CONDITIONAL_EXPORT
    void
    set_vertical_padding (
        int new_vertical_padding
    )
    noexcept;

    NUX_CONDITIONAL_EXPORT
    void
    update_layout_horizontally ()
    noexcept;

    NUX_CONDITIONAL_EXPORT
    void
    update_layout_vertically ()
    noexcept;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif
