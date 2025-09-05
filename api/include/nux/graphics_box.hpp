// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUX_GRAPHICS_BOX_HPP_INCLUDED
#define NUX_GRAPHICS_BOX_HPP_INCLUDED

#include <nux/widget.hpp>
#include <nux/matrix4x4.hpp>
#include <nux/vector_path.hpp>
#include <nux/paint.hpp>
#include <nux/graphics_native_handle.hpp>

namespace nux {

namespace impl {

class nux_opengl_widget;

} // namespace ----------------------------------------------------------------

class NUX_CONDITIONAL_EXPORT_CLASS graphics_box
    : public widget
{
public:
    // Constants --------------------------------------------------------------

    static constexpr native_widget_kind g_kind{
        native_widget_kind::graphics_box
    };

    // Constructors and Destructor --------------------------------------------

    NUX_CONDITIONAL_EXPORT
    explicit
    graphics_box (
        layout& enclosing_layout
    );

    NUX_CONDITIONAL_EXPORT
    graphics_box (
        const widget_native_handle& parent_widget_handle,
        layout& enclosing_layout
    );

    NUX_CONDITIONAL_EXPORT
    ~graphics_box ()
    noexcept override;

    // Accessors --------------------------------------------------------------

    NUX_CONDITIONAL_EXPORT
    void
    get_preferred_size (
        int& width,
        int& height
    )
    const noexcept override;

    NUX_CONDITIONAL_EXPORT
    void
    set_render_event_handler (
        const std::function<void()>& new_render_event_handler
    )
    noexcept;

    // Core -------------------------------------------------------------------

    NUX_CONDITIONAL_EXPORT
    void
    clear (
        float red,
        float green,
        float blue,
        float alpha
    );

    NUX_CONDITIONAL_EXPORT
    void
    fill_path (
        const vector_path& path,
        const paint& fill_paint
    );

    NUX_CONDITIONAL_EXPORT
    void
    stroke_path (
        const vector_path& path,
        const paint& stroke_paint
    );

    NUX_CONDITIONAL_EXPORT
    void
    present ();

    NUX_CONDITIONAL_EXPORT
    void
    render ();

    void
    handle_resize_event ()
    override;

    // Friends ----------------------------------------------------------------

    friend class impl::nux_opengl_widget;

private:
    // Private Data -----------------------------------------------------------

#if defined(NUX_OS_WINDOWS)
    bool m_should_resize;
#endif

    graphics_native_handle* m_graphics_handle;
    matrix4x4<float> m_projection;
    std::function<void()> m_render_event_handler;

    // Private Functions ------------------------------------------------------

    void
    initialize ();

#if defined(NUX_OS_WINDOWS)
    void
    resize ();
#endif

#if defined(NUX_OS_LINUX_BASED)
    void
    render_core ();
#endif

    void
    render_path (
        const vector_path& path,
        const paint& render_paint,
        bool fill
    );
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif
