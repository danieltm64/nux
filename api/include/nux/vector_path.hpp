// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUX_VECTOR_PATH_HPP_INCLUDED
#define NUX_VECTOR_PATH_HPP_INCLUDED

#include <nux/gvector2d.hpp>
#include <nux/graphics_native_handle.hpp>

#include <vector>

namespace nux {

class graphics_box;

namespace impl {

class buffer_native_handle;

class buffer {
public:
    // Constructors and Destructor --------------------------------------------

    NUX_CONDITIONAL_EXPORT
    explicit
    buffer ();

    NUX_CONDITIONAL_EXPORT
    ~buffer ()
    noexcept;

    // Accessors --------------------------------------------------------------

    NUX_CONDITIONAL_EXPORT
    buffer_native_handle&
    grab_native_handle ()
    noexcept;

    NUX_CONDITIONAL_EXPORT
    const buffer_native_handle&
    grab_native_handle ()
    const noexcept;

    NUX_CONDITIONAL_EXPORT
    bool
    is_ready ()
    const noexcept;

    NUX_CONDITIONAL_EXPORT
    std::size_t
    get_size ()
    const noexcept;

    // Core -------------------------------------------------------------------

    NUX_CONDITIONAL_EXPORT
    void
    upload (
        graphics_native_handle& graphics_handle,
        const std::vector<gvector2d<float>>& vertices
    )
    const;

private:
    // Private Data -----------------------------------------------------------

    buffer_native_handle* m_native_handle;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

enum class path_command_type {
    move_to,
    line_to,
    quad_to,
    cubic_to,
    close
}; // enum --------------------------------------------------------------------

class path_command {
public:
    // Public Data ------------------------------------------------------------

    path_command_type type;
    gvector2d<float> point;
    gvector2d<float> control1;
    gvector2d<float> control2;
}; // class -------------------------------------------------------------------

class vector_path {
public:
    // Core -------------------------------------------------------------------

    NUX_CONDITIONAL_EXPORT
    void
    begin_path (
        float x,
        float y
    );

    NUX_CONDITIONAL_EXPORT
    void
    line_to (
        float x,
        float y
    );

    NUX_CONDITIONAL_EXPORT
    void
    quad_to (
        float cx,
        float cy,
        float x,
        float y
    );

    NUX_CONDITIONAL_EXPORT
    void
    cubic_to (
        float cx1,
        float cy1,
        float cx2,
        float cy2,
        float x,
        float y
    );

    NUX_CONDITIONAL_EXPORT
    void
    close ();

    NUX_CONDITIONAL_EXPORT
    void
    end_path ();

    NUX_CONDITIONAL_EXPORT
    static
    vector_path
    build_rectangle (
        float x,
        float y,
        float width,
        float height,
        float radius = 0.0f
    );

    NUX_CONDITIONAL_EXPORT
    static
    vector_path
    build_circle (
        float center_x,
        float center_y,
        float radius
    );

    // Accessors --------------------------------------------------------------

    NUX_CONDITIONAL_EXPORT
    const std::vector<gvector2d<float>>&
    grab_vertices ()
    const;

    // Friends ----------------------------------------------------------------

    friend class graphics_box;

private:
    // Private Data -----------------------------------------------------------

    std::vector<path_command> m_commands;
    std::vector<gvector2d<float>> m_tessellated_vertices;
    impl::buffer m_buffer;

    // Private Functions ------------------------------------------------------

    void
    move_to (
        float x,
        float y
    );

    void
    tessellate ();

    void
    tessellate_quadratic (
        const gvector2d<float>& p0,
        const gvector2d<float>& p1,
        const gvector2d<float>& p2
    );

    void
    tessellate_cubic (
        const gvector2d<float>& p0,
        const gvector2d<float>& p1,
        const gvector2d<float>& p2,
        const gvector2d<float>& p3
    );

    void
    convert_fan_to_strip ();

    impl::buffer&
    grab_buffer ()
    noexcept;

    const impl::buffer&
    grab_buffer ()
    const noexcept;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif
