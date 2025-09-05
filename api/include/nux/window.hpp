// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUX_WINDOW_HPP_INCLUDED
#define NUX_WINDOW_HPP_INCLUDED

#include <nux/string.hpp>
#include <nux/window_native_handle.hpp>
#include <nux/layout.hpp>
#include <nux/key_event.hpp>
#include <nux/close_event.hpp>

#include <chrono>

namespace nux {

class window;

namespace impl {

void
update_window (
    window* w
);

void
forward_resize_event_to_window (
    void* window_handle
);

} // namespace ----------------------------------------------------------------

enum class window_mode {
    standard,
    maximized,
    minimized
}; // enum --------------------------------------------------------------------

class NUX_CONDITIONAL_EXPORT_CLASS window {
public:
    // Constructors and Destructor --------------------------------------------

    NUX_CONDITIONAL_EXPORT
    window (
        nux::string_view initial_title,
        int initial_width,
        int initial_height,
        window_mode initial_mode
    );

    NUX_CONDITIONAL_EXPORT
    virtual
    ~window ()
    noexcept;

    // Accessors --------------------------------------------------------------

    NUX_CONDITIONAL_EXPORT
    window_native_handle&
    grab_native_handle ()
    noexcept;

    NUX_CONDITIONAL_EXPORT
    const window_native_handle&
    grab_native_handle ()
    const noexcept;

    NUX_CONDITIONAL_EXPORT
    layout&
    grab_root_layout ()
    noexcept;

    NUX_CONDITIONAL_EXPORT
    const layout&
    grab_root_layout ()
    const noexcept;

    NUX_CONDITIONAL_EXPORT
    void
    get_size (
        int& width,
        int& height
    )
    const noexcept;

    NUX_CONDITIONAL_EXPORT
    void
    set_size (
        int new_width,
        int new_height
    )
    noexcept;

    NUX_CONDITIONAL_EXPORT
    nux::string
    get_title ()
    const;

    NUX_CONDITIONAL_EXPORT
    void
    set_title (
        nux::string_view new_title
    );

    NUX_CONDITIONAL_EXPORT
    bool
    is_visible ()
    const noexcept;

    // Core -------------------------------------------------------------------

    NUX_CONDITIONAL_EXPORT
    void
    show ()
    noexcept;

    NUX_CONDITIONAL_EXPORT
    void
    hide ()
    noexcept;

    NUX_CONDITIONAL_EXPORT
    void
    close ()
    noexcept;

    NUX_CONDITIONAL_EXPORT
    void
    center ()
    noexcept;

    NUX_CONDITIONAL_EXPORT
    virtual
    void
    update (
        double delta_seconds,
        double total_seconds
    );

    NUX_CONDITIONAL_EXPORT
    virtual
    void
    handle_key_down_event (
        key_event& ev
    );

    NUX_CONDITIONAL_EXPORT
    virtual
    void
    handle_key_up_event (
        key_event& ev
    );

    NUX_CONDITIONAL_EXPORT
    virtual
    void
    handle_resize_event ();

    NUX_CONDITIONAL_EXPORT
    virtual
    void
    handle_close_event (
        close_event& ev
    );

    // Friends ----------------------------------------------------------------

    friend
    void
    impl::update_window (
        window* w
    );

    friend
    void
    impl::forward_resize_event_to_window (
        void* window_handle
    );

private:
    // Private Data -----------------------------------------------------------

    window_native_handle* m_native_handle;
    std::chrono::steady_clock::time_point m_start_time;
    std::chrono::steady_clock::time_point m_last_time;
    layout m_root_layout;

    // Private Functions ------------------------------------------------------

    void
    update_root_layout ()
    noexcept;

    void
    render_graphics_boxes (
        std::vector<std::unique_ptr<window_element>>& window_elements
    );
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif
