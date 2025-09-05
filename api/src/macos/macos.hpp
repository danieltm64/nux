// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUX_MACOS_HPP_INCLUDED
#define NUX_MACOS_HPP_INCLUDED

#include <nux/string.hpp>
#include <nux/widget.hpp>

#include <vector>

#include <AppKit/AppKit.h>
#include <OpenGL/gl3.h>

namespace nux {

class window;

class NUX_CONDITIONAL_EXPORT_CLASS application_native_handle {
public:
    // Public Data ------------------------------------------------------------

    void* shared_application;
    std::vector<std::pair<void*, window*>> window_associations;
}; // class -------------------------------------------------------------------

class NUX_CONDITIONAL_EXPORT_CLASS window_native_handle {
public:
    // Public Data ------------------------------------------------------------

    NSResponder* nux_window_handle;
    bool has_been_shown;
}; // class -------------------------------------------------------------------

class NUX_CONDITIONAL_EXPORT_CLASS layout_native_handle {
}; // class -------------------------------------------------------------------

class NUX_CONDITIONAL_EXPORT_CLASS widget_native_handle {
public:
    // Public Data ------------------------------------------------------------

    NSResponder* parent_handle;
    NSView* widget_handle;
}; // class -------------------------------------------------------------------

class NUX_CONDITIONAL_EXPORT_CLASS graphics_native_handle {
public:
    // Public Data ------------------------------------------------------------

    GLuint m_shader_program;
    GLuint m_vao;
    GLuint m_vbo;
}; // class -------------------------------------------------------------------

namespace impl {

class NUX_CONDITIONAL_EXPORT_CLASS buffer_native_handle {
public:
    // Public Data ------------------------------------------------------------

    GLuint buffer;
    GLuint vao;
    std::size_t size;
}; // class -------------------------------------------------------------------

NSString*
to_nsstring (
    nux::string_view input
);

nux::string
to_nux_string (
    NSString* input
);

widget_native_handle
create_widget (
    NSResponder* parent_handle,
    native_widget_kind kind
)
noexcept;

GLuint
compile_shader (
    GLenum type,
    const char* source
);

} // namespace ----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif
