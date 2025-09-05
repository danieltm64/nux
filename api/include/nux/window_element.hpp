// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUX_WINDOW_ELEMENT_HPP_INCLUDED
#define NUX_WINDOW_ELEMENT_HPP_INCLUDED

#include <nux/core.hpp>

namespace nux {

enum class alignment {
    start,
    middle,
    end
}; // enum --------------------------------------------------------------------

enum class size_constraint {
    none,
    preferred_contracting,
    preferred_fixed,
    preferred_expanding
}; // enum --------------------------------------------------------------------

class NUX_CONDITIONAL_EXPORT_CLASS window_element {
public:
    // Constructors and Destructor --------------------------------------------

    NUX_CONDITIONAL_EXPORT
    window_element ()
    noexcept;

    virtual
    ~window_element ()
    noexcept = default;

    // Accessors --------------------------------------------------------------

    NUX_CONDITIONAL_EXPORT
    alignment
    get_alignment ()
    const noexcept;

    NUX_CONDITIONAL_EXPORT
    void
    set_alignment (
        alignment new_alignment
    );

    NUX_CONDITIONAL_EXPORT
    size_constraint
    get_size_constraint ()
    const noexcept;

    NUX_CONDITIONAL_EXPORT
    void
    set_size_constraint (
        size_constraint new_size_constraint
    );

    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    int
    get_x ()
    const noexcept;

    NUX_CONDITIONAL_EXPORT
    virtual
    void
    set_x (
        int new_x
    )
    noexcept;

    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    int
    get_y ()
    const noexcept;

    NUX_CONDITIONAL_EXPORT
    virtual
    void
    set_y (
        int new_y
    )
    noexcept;

    virtual
    void
    get_position (
        int& x,
        int& y
    )
    const noexcept = 0;

    NUX_CONDITIONAL_EXPORT
    virtual
    void
    set_position (
        int new_x,
        int new_y
    )
    noexcept;

    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    int
    get_width ()
    const noexcept;

    NUX_CONDITIONAL_EXPORT
    virtual
    void
    set_width (
        int new_width
    )
    noexcept;

    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    int
    get_height ()
    const noexcept;

    NUX_CONDITIONAL_EXPORT
    virtual
    void
    set_height (
        int new_height
    )
    noexcept;

    virtual
    void
    get_size (
        int& width,
        int& height
    )
    const noexcept = 0;

    NUX_CONDITIONAL_EXPORT
    virtual
    void
    set_size (
        int new_width,
        int new_height
    )
    noexcept;

    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    virtual
    int
    get_preferred_width ()
    const noexcept;

    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    virtual
    int
    get_preferred_height ()
    const noexcept;

    virtual
    void
    get_preferred_size (
        int& width,
        int& height
    )
    const noexcept = 0;

    NUX_CONDITIONAL_EXPORT
    virtual
    int
    get_left_overhead ()
    const noexcept;

    NUX_CONDITIONAL_EXPORT
    virtual
    int
    get_right_overhead ()
    const noexcept;

    NUX_CONDITIONAL_EXPORT
    virtual
    int
    get_top_overhead ()
    const noexcept;

    NUX_CONDITIONAL_EXPORT
    virtual
    int
    get_bottom_overhead ()
    const noexcept;

    NUX_CONDITIONAL_EXPORT
    int
    get_horizontal_overhead ()
    const noexcept;

    NUX_CONDITIONAL_EXPORT
    int
    get_vertical_overhead ()
    const noexcept;

    [[nodiscard]]
    NUX_CONDITIONAL_EXPORT
    virtual
    bool
    is_dynamically_sized ()
    const noexcept;

    NUX_CONDITIONAL_EXPORT
    virtual
    void
    set_dynamically_sized (
        bool new_dynamically_sized
    )
    noexcept;

    // Core -------------------------------------------------------------------

    NUX_CONDITIONAL_EXPORT
    void
    apply_preferred_size ()
    noexcept;

    virtual
    void
    show ()
    noexcept = 0;

    virtual
    void
    hide ()
    noexcept = 0;

    NUX_CONDITIONAL_EXPORT
    virtual
    void
    handle_resize_event ();

    NUX_CONDITIONAL_EXPORT
    virtual
    void
    handle_dpi_update_event (
        int old_dpi,
        int new_dpi
    );

    // Friends ----------------------------------------------------------------

    friend class layout;

protected:
    // Protected Functions ----------------------------------------------------

    virtual
    bool
    is_geometry_modification_prohibited ()
    const noexcept = 0;

    virtual
    void
    set_position_forcefully (
        int new_x,
        int new_y
    )
    noexcept = 0;

    virtual
    void
    set_size_forcefully (
        int new_width,
        int new_height
    )
    noexcept = 0;

private:
    // Private Data -----------------------------------------------------------

    bool m_is_dynamically_sized;
    alignment m_alignment;
    size_constraint m_size_constraint;

    // Private Functions ------------------------------------------------------

    void
    set_x_forcefully (
        int new_x
    )
    noexcept;

    void
    set_y_forcefully (
        int new_y
    )
    noexcept;

    void
    set_width_forcefully (
        int new_width
    )
    noexcept;

    void
    set_height_forcefully (
        int new_height
    )
    noexcept;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif